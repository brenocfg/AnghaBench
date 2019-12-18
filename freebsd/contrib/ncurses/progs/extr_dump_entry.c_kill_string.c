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
struct TYPE_4__ {char** Strings; } ;
typedef  TYPE_1__ TERMTYPE ;

/* Variables and functions */
 char* ABSENT_STRING ; 
 int FALSE ; 
 unsigned int NUM_STRINGS (TYPE_1__*) ; 
 int TRUE ; 

__attribute__((used)) static bool
kill_string(TERMTYPE *tterm, char *cap)
{
    unsigned n;
    for (n = 0; n < NUM_STRINGS(tterm); ++n) {
	if (cap == tterm->Strings[n]) {
	    tterm->Strings[n] = ABSENT_STRING;
	    return TRUE;
	}
    }
    return FALSE;
}