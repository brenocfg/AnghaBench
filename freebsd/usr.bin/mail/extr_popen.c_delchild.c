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
struct child {struct child* link; } ;

/* Variables and functions */
 struct child* child ; 
 struct child* child_freelist ; 

__attribute__((used)) static void
delchild(struct child *cp)
{
	struct child **cpp;

	for (cpp = &child; *cpp != cp; cpp = &(*cpp)->link)
		;
	*cpp = cp->link;
	cp->link = child_freelist;
	child_freelist = cp;
}