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
struct message {int /*<<< orphan*/  m_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDELETED ; 
 struct message* dot ; 
 struct message* message ; 
 int msgCount ; 
 int /*<<< orphan*/  touch (struct message*) ; 

int
undeletecmd(void *v)
{
	int *msgvec = v;
	int *ip;
	struct message *mp;

	for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++) {
		mp = &message[*ip - 1];
		touch(mp);
		dot = mp;
		mp->m_flag &= ~MDELETED;
	}
	return (0);
}