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
struct TYPE_4__ {int /*<<< orphan*/  returnNowBuf; } ;
typedef  TYPE_1__ testingT ;

/* Variables and functions */
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  runDefers (TYPE_1__*) ; 

__attribute__((used)) static void returnNow(testingT *t)
{
	// run defers before calling longjmp() just to be safe
	runDefers(t);
	longjmp(t->returnNowBuf, 1);
}