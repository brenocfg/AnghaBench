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
struct mbuf {int dummy; } ;
struct krb5_key_state {struct des3_state* ks_priv; } ;
struct des3_state {int /*<<< orphan*/  ds_lock; int /*<<< orphan*/  ds_session; } ;
struct cryptop {int crp_flags; int /*<<< orphan*/  crp_callback; void* crp_opaque; void* crp_buf; int /*<<< orphan*/  crp_session; struct cryptodesc* crp_desc; } ;
struct cryptodesc {size_t crd_skip; size_t crd_len; int crd_flags; int /*<<< orphan*/  crd_alg; int /*<<< orphan*/ * crd_next; int /*<<< orphan*/  crd_iv; } ;

/* Variables and functions */
 int CRD_F_IV_EXPLICIT ; 
 int CRD_F_IV_PRESENT ; 
 int CRYPTOCAP_F_SYNC ; 
 int /*<<< orphan*/  CRYPTO_3DES_CBC ; 
 int CRYPTO_F_CBIFSYNC ; 
 int CRYPTO_F_DONE ; 
 int CRYPTO_F_IMBUF ; 
 int /*<<< orphan*/  bcopy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int crypto_dispatch (struct cryptop*) ; 
 int /*<<< orphan*/  crypto_freereq (struct cryptop*) ; 
 struct cryptop* crypto_getreq (int) ; 
 int crypto_ses2caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des3_crypto_cb ; 
 int msleep (struct cryptop*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
des3_encrypt_1(const struct krb5_key_state *ks, struct mbuf *inout,
    size_t skip, size_t len, void *ivec, int encdec)
{
	struct des3_state *ds = ks->ks_priv;
	struct cryptop *crp;
	struct cryptodesc *crd;
	int error;

	crp = crypto_getreq(1);
	crd = crp->crp_desc;

	crd->crd_skip = skip;
	crd->crd_len = len;
	crd->crd_flags = CRD_F_IV_EXPLICIT | CRD_F_IV_PRESENT | encdec;
	if (ivec) {
		bcopy(ivec, crd->crd_iv, 8);
	} else {
		bzero(crd->crd_iv, 8);
	}
	crd->crd_next = NULL;
	crd->crd_alg = CRYPTO_3DES_CBC;

	crp->crp_session = ds->ds_session;
	crp->crp_flags = CRYPTO_F_IMBUF | CRYPTO_F_CBIFSYNC;
	crp->crp_buf = (void *) inout;
	crp->crp_opaque = (void *) ds;
	crp->crp_callback = des3_crypto_cb;

	error = crypto_dispatch(crp);

	if ((crypto_ses2caps(ds->ds_session) & CRYPTOCAP_F_SYNC) == 0) {
		mtx_lock(&ds->ds_lock);
		if (!error && !(crp->crp_flags & CRYPTO_F_DONE))
			error = msleep(crp, &ds->ds_lock, 0, "gssdes3", 0);
		mtx_unlock(&ds->ds_lock);
	}

	crypto_freereq(crp);
}