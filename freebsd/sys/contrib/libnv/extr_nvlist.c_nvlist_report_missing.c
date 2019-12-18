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
 int /*<<< orphan*/  PJDLOG_ABORT (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvpair_type_string (int) ; 

void
nvlist_report_missing(int type, const char *name)
{

	PJDLOG_ABORT("Element '%s' of type %s doesn't exist.",
	    name, nvpair_type_string(type));
}