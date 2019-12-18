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
struct xlp_sec_softc {int dummy; } ;
struct xlp_sec_command {int /*<<< orphan*/  iv; TYPE_1__* ses; struct cryptop* crp; } ;
struct cryptop {int /*<<< orphan*/  crp_buf; int /*<<< orphan*/  crp_flags; } ;
struct cryptodesc {scalar_t__ crd_alg; int crd_flags; int /*<<< orphan*/  crd_inject; int /*<<< orphan*/  crd_iv; } ;
struct TYPE_2__ {int /*<<< orphan*/  ses_iv; } ;

/* Variables and functions */
 int CRD_F_ENCRYPT ; 
 int CRD_F_IV_EXPLICIT ; 
 int CRD_F_IV_PRESENT ; 
 scalar_t__ CRYPTO_AES_CBC ; 
 scalar_t__ CRYPTO_ARC4 ; 
 unsigned int XLP_SEC_AES_IV_LENGTH ; 
 unsigned int XLP_SEC_DES_IV_LENGTH ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  crypto_copyback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_copydata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xlp_copyiv(struct xlp_sec_softc *sc, struct xlp_sec_command *cmd,
    struct cryptodesc *enccrd)
{
	unsigned int ivlen = 0;
	struct cryptop *crp = NULL;

	crp = cmd->crp;

	if (enccrd->crd_alg != CRYPTO_ARC4) {
		ivlen = ((enccrd->crd_alg == CRYPTO_AES_CBC) ?
		    XLP_SEC_AES_IV_LENGTH : XLP_SEC_DES_IV_LENGTH);
		if (enccrd->crd_flags & CRD_F_ENCRYPT) {
			if (enccrd->crd_flags & CRD_F_IV_EXPLICIT) {
				bcopy(enccrd->crd_iv, cmd->iv, ivlen);
			} else {
				bcopy(cmd->ses->ses_iv, cmd->iv, ivlen);
			}
			if ((enccrd->crd_flags & CRD_F_IV_PRESENT) == 0) {
				crypto_copyback(crp->crp_flags,
				    crp->crp_buf, enccrd->crd_inject,
				    ivlen, cmd->iv);
			}
		} else {
			if (enccrd->crd_flags & CRD_F_IV_EXPLICIT) {
				bcopy(enccrd->crd_iv, cmd->iv, ivlen);
			} else {
				crypto_copydata(crp->crp_flags, crp->crp_buf,
				    enccrd->crd_inject, ivlen, cmd->iv);
			}
		}
	}
	return (0);
}