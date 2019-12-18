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
struct rad_server {int /*<<< orphan*/ * secret; } ;
struct rad_handle {size_t srv; size_t out_len; int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; struct rad_server* servers; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 size_t LEN_AUTH ; 
 int /*<<< orphan*/  MD5Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t POS_ATTRS ; 
 size_t POS_AUTH ; 
 size_t POS_CODE ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
insert_request_authenticator(struct rad_handle *h, int resp)
{
	MD5_CTX ctx;
	const struct rad_server *srvp;

	srvp = &h->servers[h->srv];

	/* Create the request authenticator */
	MD5Init(&ctx);
	MD5Update(&ctx, &h->out[POS_CODE], POS_AUTH - POS_CODE);
	if (resp)
	    MD5Update(&ctx, &h->in[POS_AUTH], LEN_AUTH);
	else
	    MD5Update(&ctx, &h->out[POS_AUTH], LEN_AUTH);
	MD5Update(&ctx, &h->out[POS_ATTRS], h->out_len - POS_ATTRS);
	MD5Update(&ctx, srvp->secret, strlen(srvp->secret));
	MD5Final(&h->out[POS_AUTH], &ctx);
}