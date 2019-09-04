#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* str; struct TYPE_5__* link; } ;
typedef  TYPE_1__* List ;

/* Variables and functions */
 TYPE_1__* alloc (int) ; 

__attribute__((used)) static List append(char *str, List list) {
	List p = alloc(sizeof *p);

	p->str = str;
	if (list) {
		p->link = list->link;
		list->link = p;
	} else
		p->link = p;
	return p;
}