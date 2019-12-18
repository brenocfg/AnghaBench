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
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  ill_act ;
struct TYPE_2__ {int* stfle; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_s390x_facilities () ; 
 TYPE_1__ OPENSSL_s390xcap_P ; 
 int /*<<< orphan*/  OPENSSL_vx_probe () ; 
 int S390X_CAPBIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S390X_VX ; 
 int /*<<< orphan*/  S390X_VXD ; 
 int /*<<< orphan*/  S390X_VXE ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  ill_handler ; 
 int /*<<< orphan*/  ill_jmp ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 

void OPENSSL_cpuid_setup(void)
{
    sigset_t oset;
    struct sigaction ill_act, oact_ill, oact_fpe;

    if (OPENSSL_s390xcap_P.stfle[0])
        return;

    /* set a bit that will not be tested later */
    OPENSSL_s390xcap_P.stfle[0] |= S390X_CAPBIT(0);

    memset(&ill_act, 0, sizeof(ill_act));
    ill_act.sa_handler = ill_handler;
    sigfillset(&ill_act.sa_mask);
    sigdelset(&ill_act.sa_mask, SIGILL);
    sigdelset(&ill_act.sa_mask, SIGFPE);
    sigdelset(&ill_act.sa_mask, SIGTRAP);
    sigprocmask(SIG_SETMASK, &ill_act.sa_mask, &oset);
    sigaction(SIGILL, &ill_act, &oact_ill);
    sigaction(SIGFPE, &ill_act, &oact_fpe);

    /* protection against missing store-facility-list-extended */
    if (sigsetjmp(ill_jmp, 1) == 0)
        OPENSSL_s390x_facilities();

    /* protection against disabled vector facility */
    if ((OPENSSL_s390xcap_P.stfle[2] & S390X_CAPBIT(S390X_VX))
        && (sigsetjmp(ill_jmp, 1) == 0)) {
        OPENSSL_vx_probe();
    } else {
        OPENSSL_s390xcap_P.stfle[2] &= ~(S390X_CAPBIT(S390X_VX)
                                         | S390X_CAPBIT(S390X_VXD)
                                         | S390X_CAPBIT(S390X_VXE));
    }

    sigaction(SIGFPE, &oact_fpe, NULL);
    sigaction(SIGILL, &oact_ill, NULL);
    sigprocmask(SIG_SETMASK, &oset, NULL);
}