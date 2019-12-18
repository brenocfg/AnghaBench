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
struct message {int /*<<< orphan*/  m_size; int /*<<< orphan*/  m_lines; } ;

/* Variables and functions */
 struct message* message ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
messize(void *v)
{
	int *msgvec = v;
	struct message *mp;
	int *ip, mesg;

	for (ip = msgvec; *ip != 0; ip++) {
		mesg = *ip;
		mp = &message[mesg-1];
		printf("%d: %ld/%ld\n", mesg, mp->m_lines, mp->m_size);
	}
	return (0);
}