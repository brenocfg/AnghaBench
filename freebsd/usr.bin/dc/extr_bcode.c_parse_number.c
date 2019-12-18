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
struct TYPE_2__ {size_t readsp; int /*<<< orphan*/  scale; int /*<<< orphan*/  ibase; int /*<<< orphan*/ * readstack; } ;

/* Variables and functions */
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  push_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unreadch () ; 

__attribute__((used)) static void
parse_number(void)
{

	unreadch();
	push_number(readnumber(&bmachine.readstack[bmachine.readsp],
	    bmachine.ibase, bmachine.scale));
}