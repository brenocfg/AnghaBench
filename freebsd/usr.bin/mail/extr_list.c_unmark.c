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
struct TYPE_2__ {int /*<<< orphan*/  m_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMARK ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 TYPE_1__* message ; 
 int msgCount ; 

void
unmark(int mesg)
{
	int i;

	i = mesg;
	if (i < 1 || i > msgCount)
		errx(1, "Bad message number to unmark");
	message[i-1].m_flag &= ~MMARK;
}