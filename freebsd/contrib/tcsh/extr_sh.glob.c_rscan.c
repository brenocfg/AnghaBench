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
typedef  scalar_t__ Char ;

/* Variables and functions */
 void stub1 (scalar_t__) ; 

void
rscan(Char **t, void (*f) (Char))
{
    Char *p;

    while ((p = *t++) != NULL)
	while (*p)
	    (*f) (*p++);
}