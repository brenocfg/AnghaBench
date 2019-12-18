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
struct ignoretab {struct ignore** i_head; } ;
struct ignore {char* i_field; struct ignore* i_link; } ;

/* Variables and functions */
 scalar_t__ equal (char*,char*) ; 
 size_t hash (char*) ; 

int
member(char *realfield, struct ignoretab *table)
{
	struct ignore *igp;

	for (igp = table->i_head[hash(realfield)]; igp != NULL; igp = igp->i_link)
		if (*igp->i_field == *realfield &&
		    equal(igp->i_field, realfield))
			return (1);
	return (0);
}