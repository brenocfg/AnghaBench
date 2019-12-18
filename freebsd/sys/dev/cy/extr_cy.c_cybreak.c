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
struct tty {struct com_s* t_sc; } ;
struct com_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD1400_ETC_SENDBREAK ; 
 int /*<<< orphan*/  CD1400_ETC_STOPBREAK ; 
 int /*<<< orphan*/  cd_etc (struct com_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cybreak(struct tty *tp, int sig)
{
	struct com_s	*com;

	com = tp->t_sc;
	if (sig)
		cd_etc(com, CD1400_ETC_SENDBREAK);
	else
		cd_etc(com, CD1400_ETC_STOPBREAK);
}