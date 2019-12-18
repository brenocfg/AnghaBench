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
struct TYPE_3__ {int speed; scalar_t__ string; } ;
typedef  TYPE_1__ SPEEDS ;

/* Variables and functions */
 int /*<<< orphan*/  CaselessCmp (char*,scalar_t__) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  err (char*,char*) ; 
 TYPE_1__* speeds ; 

__attribute__((used)) static int
tbaudrate(char *rate)
{
    const SPEEDS *sp;
    int found = FALSE;

    /* The baudrate number can be preceded by a 'B', which is ignored. */
    if (*rate == 'B')
	++rate;

    for (sp = speeds; sp->string; ++sp) {
	if (!CaselessCmp(rate, sp->string)) {
	    found = TRUE;
	    break;
	}
    }
    if (!found)
	err("unknown baud rate %s", rate);
    return (sp->speed);
}