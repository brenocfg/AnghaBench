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
struct message {int m_flag; } ;

/* Variables and functions */
 int MDELETED ; 
 struct message* message ; 
 int msgCount ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
check(int mesg, int f)
{
	struct message *mp;

	if (mesg < 1 || mesg > msgCount) {
		printf("%d: Invalid message number\n", mesg);
		return (-1);
	}
	mp = &message[mesg-1];
	if (f != MDELETED && (mp->m_flag & MDELETED) != 0) {
		printf("%d: Inappropriate message\n", mesg);
		return (-1);
	}
	return (0);
}