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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct rad_server {int /*<<< orphan*/  secret; } ;
struct rad_handle {size_t srv; int authentic_pos; size_t out_len; int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; struct rad_server* servers; } ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t LEN_AUTH ; 
 size_t POS_ATTRS ; 
 size_t POS_AUTH ; 
 size_t POS_CODE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
insert_message_authenticator(struct rad_handle *h, int resp)
{
#ifdef WITH_SSL
	u_char md[EVP_MAX_MD_SIZE];
	u_int md_len;
	const struct rad_server *srvp;
	HMAC_CTX *ctx;
	srvp = &h->servers[h->srv];

	if (h->authentic_pos != 0) {
		ctx = HMAC_CTX_new();
		HMAC_Init_ex(ctx, srvp->secret, strlen(srvp->secret), EVP_md5(), NULL);
		HMAC_Update(ctx, &h->out[POS_CODE], POS_AUTH - POS_CODE);
		if (resp)
		    HMAC_Update(ctx, &h->in[POS_AUTH], LEN_AUTH);
		else
		    HMAC_Update(ctx, &h->out[POS_AUTH], LEN_AUTH);
		HMAC_Update(ctx, &h->out[POS_ATTRS],
		    h->out_len - POS_ATTRS);
		HMAC_Final(ctx, md, &md_len);
		HMAC_CTX_free(ctx);
		memcpy(&h->out[h->authentic_pos + 2], md, md_len);
	}
#endif
}