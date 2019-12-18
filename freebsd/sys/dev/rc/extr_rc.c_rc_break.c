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
struct tty {struct rc_chans* t_sc; } ;
struct rc_chans {int /*<<< orphan*/  rc_pendcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD180_C_EBRK ; 
 int /*<<< orphan*/  CD180_C_SBRK ; 

__attribute__((used)) static void
rc_break(struct tty *tp, int brk)
{
	struct rc_chans *rc;

	rc = tp->t_sc;

	if (brk)
		rc->rc_pendcmd = CD180_C_SBRK;
	else
		rc->rc_pendcmd = CD180_C_EBRK;
}