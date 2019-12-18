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
typedef  scalar_t__ u8 ;
struct radius_msg {size_t attr_used; TYPE_1__* hdr; } ;
struct radius_attr_hdr {scalar_t__ type; int length; } ;
struct TYPE_2__ {scalar_t__* authenticator; } ;

/* Variables and functions */
 scalar_t__ RADIUS_ATTR_TUNNEL_PASSWORD ; 
 int /*<<< orphan*/  md5_vector (int,scalar_t__ const**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  os_free (scalar_t__*) ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,scalar_t__*,int) ; 
 scalar_t__* os_memdup (scalar_t__ const*,size_t) ; 
 struct radius_attr_hdr* radius_get_attr_hdr (struct radius_msg*,size_t) ; 

char * radius_msg_get_tunnel_password(struct radius_msg *msg, int *keylen,
				      const u8 *secret, size_t secret_len,
				      struct radius_msg *sent_msg, size_t n)
{
	u8 *buf = NULL;
	size_t buflen;
	const u8 *salt;
	u8 *str;
	const u8 *addr[3];
	size_t len[3];
	u8 hash[16];
	u8 *pos;
	size_t i, j = 0;
	struct radius_attr_hdr *attr;
	const u8 *data;
	size_t dlen;
	const u8 *fdata = NULL; /* points to found item */
	size_t fdlen = -1;
	char *ret = NULL;

	/* find n-th valid Tunnel-Password attribute */
	for (i = 0; i < msg->attr_used; i++) {
		attr = radius_get_attr_hdr(msg, i);
		if (attr == NULL ||
		    attr->type != RADIUS_ATTR_TUNNEL_PASSWORD) {
			continue;
		}
		if (attr->length <= 5)
			continue;
		data = (const u8 *) (attr + 1);
		dlen = attr->length - sizeof(*attr);
		if (dlen <= 3 || dlen % 16 != 3)
			continue;
		j++;
		if (j <= n)
			continue;

		fdata = data;
		fdlen = dlen;
		break;
	}
	if (fdata == NULL)
		goto out;

	/* alloc writable memory for decryption */
	buf = os_memdup(fdata, fdlen);
	if (buf == NULL)
		goto out;
	buflen = fdlen;

	/* init pointers */
	salt = buf + 1;
	str = buf + 3;

	/* decrypt blocks */
	pos = buf + buflen - 16; /* last block */
	while (pos >= str + 16) { /* all but the first block */
		addr[0] = secret;
		len[0] = secret_len;
		addr[1] = pos - 16;
		len[1] = 16;
		md5_vector(2, addr, len, hash);

		for (i = 0; i < 16; i++)
			pos[i] ^= hash[i];

		pos -= 16;
	}

	/* decrypt first block */
	if (str != pos)
		goto out;
	addr[0] = secret;
	len[0] = secret_len;
	addr[1] = sent_msg->hdr->authenticator;
	len[1] = 16;
	addr[2] = salt;
	len[2] = 2;
	md5_vector(3, addr, len, hash);

	for (i = 0; i < 16; i++)
		pos[i] ^= hash[i];

	/* derive plaintext length from first subfield */
	*keylen = (unsigned char) str[0];
	if ((u8 *) (str + *keylen) >= (u8 *) (buf + buflen)) {
		/* decryption error - invalid key length */
		goto out;
	}
	if (*keylen == 0) {
		/* empty password */
		goto out;
	}

	/* copy passphrase into new buffer */
	ret = os_malloc(*keylen);
	if (ret)
		os_memcpy(ret, str + 1, *keylen);

out:
	/* return new buffer */
	os_free(buf);
	return ret;
}