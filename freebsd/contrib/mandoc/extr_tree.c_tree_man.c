#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct roff_meta {scalar_t__ hasbody; TYPE_1__* first; } ;
struct TYPE_2__ {int /*<<< orphan*/  child; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_man (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_meta (struct roff_meta const*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 

void
tree_man(void *arg, const struct roff_meta *man)
{
	print_meta(man);
	if (man->hasbody == 0)
		puts("body  = empty");
	putchar('\n');
	print_man(man->first->child, 0);
}