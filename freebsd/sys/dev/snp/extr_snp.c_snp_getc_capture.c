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
struct snp_softc {int /*<<< orphan*/  snp_outpoll; int /*<<< orphan*/  snp_outwait; int /*<<< orphan*/  snp_outq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 
 struct snp_softc* ttyhook_softc (struct tty*) ; 
 int /*<<< orphan*/  ttyoutq_write (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static void
snp_getc_capture(struct tty *tp, const void *buf, size_t len)
{
	struct snp_softc *ss = ttyhook_softc(tp);

	ttyoutq_write(&ss->snp_outq, buf, len);

	cv_broadcast(&ss->snp_outwait);
	selwakeup(&ss->snp_outpoll);
}