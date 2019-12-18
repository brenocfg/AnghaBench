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
 struct message* dot ; 
 struct message* message ; 
 size_t msgCount ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  printhead (int) ; 
 int screen ; 
 int screensize () ; 

int
headers(void *v)
{
	int *msgvec = v;
	int n, mesg, flag, size;
	struct message *mp;

	size = screensize();
	n = msgvec[0];
	if (n != 0)
		screen = (n-1)/size;
	if (screen < 0)
		screen = 0;
	mp = &message[screen * size];
	if (mp >= &message[msgCount])
		mp = &message[msgCount - size];
	if (mp < &message[0])
		mp = &message[0];
	flag = 0;
	mesg = mp - &message[0];
	if (dot != &message[n-1])
		dot = mp;
	for (; mp < &message[msgCount]; mp++) {
		mesg++;
		if (mp->m_flag & MDELETED)
			continue;
		if (flag++ >= size)
			break;
		printhead(mesg);
	}
	if (flag == 0) {
		printf("No more mail.\n");
		return (1);
	}
	return (0);
}