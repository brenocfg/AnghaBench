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
 void** h2o_mem_realloc (void**,size_t) ; 

void h2o_append_to_null_terminated_list(void ***list, void *element)
{
    size_t cnt;

    for (cnt = 0; (*list)[cnt] != NULL; ++cnt)
        ;
    *list = h2o_mem_realloc(*list, (cnt + 2) * sizeof(void *));
    (*list)[cnt++] = element;
    (*list)[cnt] = NULL;
}