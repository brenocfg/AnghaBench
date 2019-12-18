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
 int MMARK ; 
 scalar_t__ markall (char*,int) ; 
 struct message* message ; 
 size_t msgCount ; 

int
getmsglist(char *buf, int *vector, int flags)
{
	int *ip;
	struct message *mp;

	if (msgCount == 0) {
		*vector = 0;
		return (0);
	}
	if (markall(buf, flags) < 0)
		return (-1);
	ip = vector;
	for (mp = &message[0]; mp < &message[msgCount]; mp++)
		if (mp->m_flag & MMARK)
			*ip++ = mp - &message[0] + 1;
	*ip = 0;
	return (ip - vector);
}