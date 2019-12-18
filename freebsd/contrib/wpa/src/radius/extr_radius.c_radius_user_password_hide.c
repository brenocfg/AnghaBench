#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct radius_msg {TYPE_1__* hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/ * authenticator; } ;

/* Variables and functions */
 int /*<<< orphan*/  md5_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

int radius_user_password_hide(struct radius_msg *msg,
			      const u8 *data, size_t data_len,
			      const u8 *secret, size_t secret_len,
			      u8 *buf, size_t buf_len)
{
	size_t padlen, i, pos;
	const u8 *addr[2];
	size_t len[2];
	u8 hash[16];

	if (data_len + 16 > buf_len)
		return -1;

	os_memcpy(buf, data, data_len);

	padlen = data_len % 16;
	if (padlen && data_len < buf_len) {
		padlen = 16 - padlen;
		os_memset(buf + data_len, 0, padlen);
		buf_len = data_len + padlen;
	} else {
		buf_len = data_len;
	}

	addr[0] = secret;
	len[0] = secret_len;
	addr[1] = msg->hdr->authenticator;
	len[1] = 16;
	md5_vector(2, addr, len, hash);

	for (i = 0; i < 16; i++)
		buf[i] ^= hash[i];
	pos = 16;

	while (pos < buf_len) {
		addr[0] = secret;
		len[0] = secret_len;
		addr[1] = &buf[pos - 16];
		len[1] = 16;
		md5_vector(2, addr, len, hash);

		for (i = 0; i < 16; i++)
			buf[pos + i] ^= hash[i];

		pos += 16;
	}

	return buf_len;
}