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

int
first(int f, int m)
{
	struct message *mp;

	if (msgCount == 0)
		return (0);
	f &= MDELETED;
	m &= MDELETED;
	for (mp = dot; mp < &message[msgCount]; mp++)
		if ((mp->m_flag & m) == f)
			return (mp - message + 1);
	for (mp = dot-1; mp >= &message[0]; mp--)
		if ((mp->m_flag & m) == f)
			return (mp - message + 1);
	return (0);
}