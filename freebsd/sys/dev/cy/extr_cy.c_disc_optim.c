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
typedef  int u_char ;
struct tty {int dummy; } ;
struct termios {int dummy; } ;
struct com_s {int* cor; TYPE_1__* tp; } ;
struct TYPE_2__ {scalar_t__ t_hotchar; } ;

/* Variables and functions */
 int CD1400_CCR_CMDCORCHG ; 
 int CD1400_CCR_COR3 ; 
 int /*<<< orphan*/  CD1400_COR3 ; 
 int CD1400_COR3_SCD34 ; 
 int /*<<< orphan*/  CD1400_SCHR3 ; 
 int /*<<< orphan*/  CD1400_SCHR4 ; 
 int /*<<< orphan*/  cd1400_channel_cmd (struct com_s*,int) ; 
 int /*<<< orphan*/  cd_setreg (struct com_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttyldoptim (struct tty*) ; 

__attribute__((used)) static void
disc_optim(struct tty *tp, struct termios *t, struct com_s *com)
{
#ifndef SOFT_HOTCHAR
	u_char	opt;
#endif

	ttyldoptim(tp);
#ifndef SOFT_HOTCHAR
	opt = com->cor[2] & ~CD1400_COR3_SCD34;
	if (com->tp->t_hotchar != 0) {
		cd_setreg(com, CD1400_SCHR3, com->tp->t_hotchar);
		cd_setreg(com, CD1400_SCHR4, com->tp->t_hotchar);
		opt |= CD1400_COR3_SCD34;
	}
	if (opt != com->cor[2]) {
		cd_setreg(com, CD1400_COR3, com->cor[2] = opt);
		cd1400_channel_cmd(com, CD1400_CCR_CMDCORCHG | CD1400_CCR_COR3);
	}
#endif
}