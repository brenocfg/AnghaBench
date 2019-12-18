#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int u_char ;
struct TYPE_4__ {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__ sin_family; scalar_t__ sin_port; TYPE_1__ sin_addr; } ;
struct TYPE_5__ {scalar_t__ s_addr; } ;
struct TYPE_6__ {scalar_t__ sin_family; scalar_t__ sin_port; TYPE_2__ sin_addr; } ;
struct rad_server {int* secret; TYPE_3__ addr; } ;
struct rad_handle {size_t in_len; int* in; int* out; struct rad_server* servers; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_CTX_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,int*,size_t) ; 
 size_t LEN_AUTH ; 
 int /*<<< orphan*/  MD5Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int*,int) ; 
 int MD5_DIGEST_LENGTH ; 
 int MSGSIZE ; 
 size_t POS_ATTRS ; 
 size_t POS_AUTH ; 
 size_t POS_CODE ; 
 size_t POS_LENGTH ; 
 int RAD_ACCOUNTING_RESPONSE ; 
 scalar_t__ RAD_MESSAGE_AUTHENTIC ; 
 scalar_t__ memcmp (int*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int strlen (int*) ; 

__attribute__((used)) static int
is_valid_response(struct rad_handle *h, int srv,
    const struct sockaddr_in *from)
{
	MD5_CTX ctx;
	unsigned char md5[MD5_DIGEST_LENGTH];
	const struct rad_server *srvp;
	int len;
#ifdef WITH_SSL
	HMAC_CTX *hctx;
	u_char resp[MSGSIZE], md[EVP_MAX_MD_SIZE];
	u_int md_len;
	int pos;
#endif

	srvp = &h->servers[srv];

	/* Check the source address */
	if (from->sin_family != srvp->addr.sin_family ||
	    from->sin_addr.s_addr != srvp->addr.sin_addr.s_addr ||
	    from->sin_port != srvp->addr.sin_port)
		return 0;

	/* Check the message length */
	if (h->in_len < POS_ATTRS)
		return 0;
	len = h->in[POS_LENGTH] << 8 | h->in[POS_LENGTH+1];
	if (len > h->in_len)
		return 0;

	/* Check the response authenticator */
	MD5Init(&ctx);
	MD5Update(&ctx, &h->in[POS_CODE], POS_AUTH - POS_CODE);
	MD5Update(&ctx, &h->out[POS_AUTH], LEN_AUTH);
	MD5Update(&ctx, &h->in[POS_ATTRS], len - POS_ATTRS);
	MD5Update(&ctx, srvp->secret, strlen(srvp->secret));
	MD5Final(md5, &ctx);
	if (memcmp(&h->in[POS_AUTH], md5, sizeof md5) != 0)
		return 0;

#ifdef WITH_SSL
	/*
	 * For non accounting responses check the message authenticator,
	 * if any.
	 */
	if (h->in[POS_CODE] != RAD_ACCOUNTING_RESPONSE) {

		memcpy(resp, h->in, MSGSIZE);
		pos = POS_ATTRS;

		/* Search and verify the Message-Authenticator */
		hctx = HMAC_CTX_new();
		while (pos < len - 2) {

			if (h->in[pos] == RAD_MESSAGE_AUTHENTIC) {
				/* zero fill the Message-Authenticator */
				memset(&resp[pos + 2], 0, MD5_DIGEST_LENGTH);

				HMAC_Init_ex(hctx, srvp->secret,
				    strlen(srvp->secret), EVP_md5(), NULL);
				HMAC_Update(hctx, &h->in[POS_CODE],
				    POS_AUTH - POS_CODE);
				HMAC_Update(hctx, &h->out[POS_AUTH],
				    LEN_AUTH);
				HMAC_Update(hctx, &resp[POS_ATTRS],
				    h->in_len - POS_ATTRS);
				HMAC_Final(hctx, md, &md_len);
				HMAC_CTX_reset(hctx);
				if (memcmp(md, &h->in[pos + 2],
				    MD5_DIGEST_LENGTH) != 0) {
					HMAC_CTX_free(hctx);
					return 0;
				}
				break;
			}
			pos += h->in[pos + 1];
		}
		HMAC_CTX_free(hctx);
	}
#endif
	return 1;
}