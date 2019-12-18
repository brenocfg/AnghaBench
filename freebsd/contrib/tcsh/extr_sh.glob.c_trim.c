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
typedef  int Char ;

/* Variables and functions */
 int INVALID_BYTE ; 
 int TRIM ; 

void
trim(Char **t)
{
    Char *p;

    while ((p = *t++) != NULL)
	while (*p) {
#if INVALID_BYTE != 0
	    if ((*p & INVALID_BYTE) != INVALID_BYTE)	/* *p < INVALID_BYTE */
#endif
		*p &= TRIM;
	    p++;
	}
}