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
struct number {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stack; } ;

/* Variables and functions */
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  stack_pushnumber (int /*<<< orphan*/ *,struct number*) ; 

__attribute__((used)) static __inline void
push_number(struct number *n)
{

	stack_pushnumber(&bmachine.stack, n);
}