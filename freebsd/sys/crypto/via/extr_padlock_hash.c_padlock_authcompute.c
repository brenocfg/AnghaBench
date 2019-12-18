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
typedef  union authctx {int dummy; } authctx ;
typedef  int /*<<< orphan*/  u_char ;
struct padlock_session {int /*<<< orphan*/  ses_mlen; int /*<<< orphan*/  ses_octx; int /*<<< orphan*/  ses_ictx; struct auth_hash* ses_axf; } ;
struct cryptodesc {int /*<<< orphan*/  crd_inject; int /*<<< orphan*/  crd_len; int /*<<< orphan*/  crd_skip; } ;
struct auth_hash {int /*<<< orphan*/  hashsize; int /*<<< orphan*/  (* Final ) (int /*<<< orphan*/ *,union authctx*) ;int /*<<< orphan*/  (* Update ) (union authctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int HASH_MAX_LEN ; 
 int crypto_apply (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int (*) (void*,void*,unsigned int),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_copyback (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  padlock_copy_ctx (struct auth_hash*,int /*<<< orphan*/ ,union authctx*) ; 
 int /*<<< orphan*/  padlock_free_ctx (struct auth_hash*,union authctx*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,union authctx*) ; 
 int /*<<< orphan*/  stub2 (union authctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,union authctx*) ; 

__attribute__((used)) static int
padlock_authcompute(struct padlock_session *ses, struct cryptodesc *crd,
    caddr_t buf, int flags)
{
	u_char hash[HASH_MAX_LEN];
	struct auth_hash *axf;
	union authctx ctx;
	int error;

	axf = ses->ses_axf;

	padlock_copy_ctx(axf, ses->ses_ictx, &ctx);
	error = crypto_apply(flags, buf, crd->crd_skip, crd->crd_len,
	    (int (*)(void *, void *, unsigned int))axf->Update, (caddr_t)&ctx);
	if (error != 0) {
		padlock_free_ctx(axf, &ctx);
		return (error);
	}
	axf->Final(hash, &ctx);

	padlock_copy_ctx(axf, ses->ses_octx, &ctx);
	axf->Update(&ctx, hash, axf->hashsize);
	axf->Final(hash, &ctx);

	/* Inject the authentication data */
	crypto_copyback(flags, buf, crd->crd_inject,
	    ses->ses_mlen == 0 ? axf->hashsize : ses->ses_mlen, hash);
	return (0);
}