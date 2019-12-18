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
struct tty {int dummy; } ;
struct snp_softc {int /*<<< orphan*/  snp_outwait; int /*<<< orphan*/  snp_outq; struct tty* snp_tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SNP ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct snp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  ttyhook_unregister (struct tty*) ; 
 int /*<<< orphan*/  ttyoutq_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
snp_dtor(void *data)
{
	struct snp_softc *ss = data;
	struct tty *tp;

	tp = ss->snp_tty;
	if (tp != NULL) {
		tty_lock(tp);
		ttyoutq_free(&ss->snp_outq);
		ttyhook_unregister(tp);
	}

	cv_destroy(&ss->snp_outwait);
	free(ss, M_SNP);
}