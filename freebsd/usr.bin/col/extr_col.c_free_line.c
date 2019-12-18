#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* l_next; } ;
typedef  TYPE_1__ LINE ;

/* Variables and functions */
 TYPE_1__* line_freelist ; 

__attribute__((used)) static void
free_line(LINE *l)
{

	l->l_next = line_freelist;
	line_freelist = l;
}