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
 int FALSE ; 
 scalar_t__ tolower (int /*<<< orphan*/ ) ; 

int tcb_strmatch_nc(char *cs, char *ct) {
    while (*cs)
        if (tolower(*cs++) != tolower(*ct++)) return (FALSE);
    return (!(*ct));  /*return TRUE if *ct NULL at same time as *cs==NULL*/
}