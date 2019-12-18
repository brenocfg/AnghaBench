#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* body; } ;
struct tac_msg {int flags; unsigned char* session_id; unsigned char version; unsigned char seq_no; TYPE_2__ u; int /*<<< orphan*/  length; } ;
struct tac_handle {size_t cur_server; TYPE_1__* servers; } ;
struct TYPE_3__ {char* secret; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,...) ; 
 int TAC_UNENCRYPTED ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
crypt_msg(struct tac_handle *h, struct tac_msg *msg)
{
	const char *secret;
	MD5_CTX base_ctx;
	MD5_CTX ctx;
	unsigned char md5[16];
	int chunk;
	int msg_len;

	secret = h->servers[h->cur_server].secret;
	if (secret[0] == '\0')
		msg->flags |= TAC_UNENCRYPTED;
	if (msg->flags & TAC_UNENCRYPTED)
		return;

	msg_len = ntohl(msg->length);

	MD5Init(&base_ctx);
	MD5Update(&base_ctx, msg->session_id, sizeof msg->session_id);
	MD5Update(&base_ctx, secret, strlen(secret));
	MD5Update(&base_ctx, &msg->version, sizeof msg->version);
	MD5Update(&base_ctx, &msg->seq_no, sizeof msg->seq_no);

	ctx = base_ctx;
	for (chunk = 0;  chunk < msg_len;  chunk += sizeof md5) {
		int chunk_len;
		int i;

		MD5Final(md5, &ctx);

		if ((chunk_len = msg_len - chunk) > sizeof md5)
			chunk_len = sizeof md5;
		for (i = 0;  i < chunk_len;  i++)
			msg->u.body[chunk + i] ^= md5[i];

		ctx = base_ctx;
		MD5Update(&ctx, md5, sizeof md5);
	}
}