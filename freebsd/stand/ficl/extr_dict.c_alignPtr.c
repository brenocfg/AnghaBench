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
struct TYPE_2__ {int u; void* p; } ;
typedef  TYPE_1__ CELL ;

/* Variables and functions */
 int FICL_ALIGN_ADD ; 

void *alignPtr(void *ptr)
{
#if FICL_ALIGN > 0
    char *cp;
    CELL c;
    cp = (char *)ptr + FICL_ALIGN_ADD;
    c.p = (void *)cp;
    c.u = c.u & (~FICL_ALIGN_ADD);
    ptr = (CELL *)c.p;
#endif
    return ptr;
}