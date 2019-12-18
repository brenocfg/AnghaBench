#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  argname; } ;
struct TYPE_5__ {TYPE_1__ args; } ;
typedef  TYPE_2__ proc_list ;

/* Variables and functions */
 int /*<<< orphan*/  print_generic_header (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_prog_header(proc_list *plist)
{
	print_generic_header(plist->args.argname, 1);
}