#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHINT (int) ; 
 int /*<<< orphan*/  PUSHPTR (void*) ; 
 void* ficlRealloc (void*,size_t) ; 
 size_t stackPopINT (int /*<<< orphan*/ ) ; 
 void* stackPopPtr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ansResize(FICL_VM *pVM)
{
    size_t size;
    void *new, *old;

    size = stackPopINT(pVM->pStack);
    old = stackPopPtr(pVM->pStack);
    new = ficlRealloc(old, size);
    if (new) 
    {
        PUSHPTR(new);
        PUSHINT(0);
    } 
    else 
    {
        PUSHPTR(old);
        PUSHINT(1);
    }
}