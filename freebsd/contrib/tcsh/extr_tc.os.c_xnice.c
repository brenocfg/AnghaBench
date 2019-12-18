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

/* Variables and functions */
 int /*<<< orphan*/  MM ; 
 int /*<<< orphan*/  NICE ; 
 int /*<<< orphan*/  NIL_PTR ; 
 int callm1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int 
xnice(int incr)
{
#if defined(_MINIX) && defined(NICE)
    return callm1(MM, NICE, incr, 0, 0, NIL_PTR, NIL_PTR, NIL_PTR);
#else
    return /* incr ? 0 : */ 0;
#endif /* _MINIX && NICE */
}