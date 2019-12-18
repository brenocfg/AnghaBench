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
struct TYPE_2__ {int /*<<< orphan*/  (* redo ) () ;int /*<<< orphan*/  (* done ) (int) ;int /*<<< orphan*/  (* error ) () ;} ;

/* Variables and functions */
 TYPE_1__* cont ; 
 int interpret_errors () ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  stub3 () ; 

__attribute__((used)) static void format_interrupt(void)
{
	switch (interpret_errors()) {
	case 1:
		cont->error();
	case 2:
		break;
	case 0:
		cont->done(1);
	}
	cont->redo();
}