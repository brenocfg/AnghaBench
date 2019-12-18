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
struct cryptop {int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_flags; struct cryptodesc* crp_desc; } ;
struct cryptodesc {int /*<<< orphan*/  crd_inject; } ;
struct cpl_fw6_pld {int dummy; } ;
struct ccr_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash_len; } ;
struct ccr_session {TYPE_1__ hmac; } ;
typedef  int /*<<< orphan*/  c_caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_copyback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ccr_hash_done(struct ccr_softc *sc, struct ccr_session *s, struct cryptop *crp,
    const struct cpl_fw6_pld *cpl, int error)
{
	struct cryptodesc *crd;

	crd = crp->crp_desc;
	if (error == 0) {
		crypto_copyback(crp->crp_flags, crp->crp_buf, crd->crd_inject,
		    s->hmac.hash_len, (c_caddr_t)(cpl + 1));
	}

	return (error);
}