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
typedef  size_t PredIdx ;

/* Variables and functions */
 char* ABSENT_STRING ; 
 size_t NUM_STRINGS (TYPE_1__*) ; 
 int /*<<< orphan*/  STRING ; 
 scalar_t__ VALID_STRING (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strnames ; 
 scalar_t__ version_filter (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static char *
find_string(TERMTYPE *tterm, char *name)
{
    PredIdx n;
    for (n = 0; n < NUM_STRINGS(tterm); ++n) {
	if (version_filter(STRING, n)
	    && !strcmp(name, strnames[n])) {
	    char *cap = tterm->Strings[n];
	    if (VALID_STRING(cap)) {
		return cap;
	    }
	    break;
	}
    }
    return ABSENT_STRING;
}