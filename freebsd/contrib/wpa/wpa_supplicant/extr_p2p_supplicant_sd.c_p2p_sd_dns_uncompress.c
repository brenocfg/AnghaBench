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
 int DNS_HEADER_LEN ; 
 int P2P_SD_IN_MEMORY_LEN ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  os_memset (char*,int /*<<< orphan*/ ,int) ; 
 int p2p_sd_dns_uncompress_label (char**,char*,char*,char**,char*) ; 

__attribute__((used)) static int p2p_sd_dns_uncompress(char *buf, size_t buf_len, const u8 *msg,
				 size_t msg_len, size_t offset)
{
	/* 27-octet in-memory packet from P2P specification */
	const char *prefix = "\x04_tcp\x05local\x00\x00\x0C\x00\x01"
		"\x04_udp\xC0\x11\x00\x0C\x00\x01";
	u8 *tmp, *end, *spos;
	char *upos, *uend;
	int ret = 0;

	if (buf_len < 2)
		return -1;
	if (offset > msg_len)
		return -1;

	tmp = os_malloc(DNS_HEADER_LEN + P2P_SD_IN_MEMORY_LEN + msg_len);
	if (tmp == NULL)
		return -1;
	spos = tmp + DNS_HEADER_LEN + P2P_SD_IN_MEMORY_LEN;
	end = spos + msg_len;
	spos += offset;

	os_memset(tmp, 0, DNS_HEADER_LEN);
	os_memcpy(tmp + DNS_HEADER_LEN, prefix, P2P_SD_IN_MEMORY_LEN);
	os_memcpy(tmp + DNS_HEADER_LEN + P2P_SD_IN_MEMORY_LEN, msg, msg_len);

	upos = buf;
	uend = buf + buf_len;

	ret = p2p_sd_dns_uncompress_label(&upos, uend, tmp, &spos, end);
	if (ret) {
		os_free(tmp);
		return ret;
	}

	if (upos == buf) {
		upos[0] = '.';
		upos[1] = '\0';
	} else if (upos[-1] == '.')
		upos[-1] = '\0';

	os_free(tmp);
	return 0;
}