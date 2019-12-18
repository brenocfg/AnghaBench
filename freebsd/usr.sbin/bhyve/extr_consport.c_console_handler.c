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
typedef  int uint32_t ;
struct vmctx {int dummy; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  cap_ioctl_t ;

/* Variables and functions */
 int BVM_CONS_SIG ; 
 int /*<<< orphan*/  CAP_EVENT ; 
 int /*<<< orphan*/  CAP_IOCTL ; 
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TIOCGETA ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  TIOCSETA ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int caph_ioctls_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int caph_rights_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttyopen () ; 
 int ttyread () ; 
 int /*<<< orphan*/  ttywrite (int) ; 

__attribute__((used)) static int
console_handler(struct vmctx *ctx, int vcpu, int in, int port, int bytes,
		uint32_t *eax, void *arg)
{
	static int opened;
#ifndef WITHOUT_CAPSICUM
	cap_rights_t rights;
	cap_ioctl_t cmds[] = { TIOCGETA, TIOCSETA, TIOCGWINSZ };
#endif

	if (bytes == 2 && in) {
		*eax = BVM_CONS_SIG;
		return (0);
	}

	/*
	 * Guests might probe this port to look for old ISA devices
	 * using single-byte reads.  Return 0xff for those.
	 */
	if (bytes == 1 && in) {
		*eax = 0xff;
		return (0);
	}

	if (bytes != 4)
		return (-1);

	if (!opened) {
#ifndef WITHOUT_CAPSICUM
		cap_rights_init(&rights, CAP_EVENT, CAP_IOCTL, CAP_READ,
		    CAP_WRITE);
		if (caph_rights_limit(STDIN_FILENO, &rights) == -1)
			errx(EX_OSERR, "Unable to apply rights for sandbox");
		if (caph_ioctls_limit(STDIN_FILENO, cmds, nitems(cmds)) == -1)
			errx(EX_OSERR, "Unable to apply rights for sandbox");
#endif
		ttyopen();
		opened = 1;
	}
	
	if (in)
		*eax = ttyread();
	else
		ttywrite(*eax);

	return (0);
}