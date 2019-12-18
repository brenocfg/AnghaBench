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
 int /*<<< orphan*/  MBOX ; 
 int /*<<< orphan*/  MPRESERVE ; 
 struct message* dot ; 
 scalar_t__ edit ; 
 struct message* message ; 
 int /*<<< orphan*/  printf (char*) ; 

int
preserve(void *v)
{
	int *msgvec = v;
	int *ip, mesg;
	struct message *mp;

	if (edit) {
		printf("Cannot \"preserve\" in edit mode\n");
		return (1);
	}
	for (ip = msgvec; *ip != 0; ip++) {
		mesg = *ip;
		mp = &message[mesg-1];
		mp->m_flag |= MPRESERVE;
		mp->m_flag &= ~MBOX;
		dot = mp;
	}
	return (0);
}