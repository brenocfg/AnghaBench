#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char u8 ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_PUT_BE16 (char*,int) ; 
 int omac1_aes_128 (char const*,char*,int,char*) ; 
 int omac1_aes_256 (char const*,char*,int,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  os_memset (char*,int /*<<< orphan*/ ,int) ; 
 int os_strlen (char const*) ; 
 char* os_zalloc (int) ; 

__attribute__((used)) static int aes_kdf(const u8 *kdk, size_t kdk_bits,
		   const char *label, const u8 *context,
		   int ctx_bits, int ret_bits, u8 *ret)
{
	const int h = 128;
	const int r = 8;
	int i, n;
	int lab_len, ctx_len, ret_len, buf_len;
	u8 *buf;

	if (kdk_bits != 128 && kdk_bits != 256)
		return -1;

	lab_len = os_strlen(label);
	ctx_len = (ctx_bits + 7) / 8;
	ret_len = ((ret_bits & 0xffff) + 7) / 8;
	buf_len = lab_len + ctx_len + 4;

	os_memset(ret, 0, ret_len);

	n = (ret_bits + h - 1) / h;
	if (n > ((0x1 << r) - 1))
		return -1;

	buf = os_zalloc(buf_len);
	if (buf == NULL)
		return -1;

	os_memcpy(buf + 1, label, lab_len);
	os_memcpy(buf + lab_len + 2, context, ctx_len);
	WPA_PUT_BE16(&buf[buf_len - 2], ret_bits);

	for (i = 0; i < n; i++) {
		int res;

		buf[0] = (u8) (i + 1);
		if (kdk_bits == 128)
			res = omac1_aes_128(kdk, buf, buf_len, ret);
		else
			res = omac1_aes_256(kdk, buf, buf_len, ret);
		if (res) {
			os_free(buf);
			return -1;
		}
		ret = ret + h / 8;
	}
	os_free(buf);
	return 0;
}