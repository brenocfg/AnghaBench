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
struct auditfilter_module {scalar_t__ (* am_reinit ) (struct auditfilter_module*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  am_modulename; int /*<<< orphan*/  am_argv; int /*<<< orphan*/  am_argc; } ;

/* Variables and functions */
 scalar_t__ AUDIT_FILTER_SUCCESS ; 
 scalar_t__ stub1 (struct auditfilter_module*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
auditfilter_module_reinit(struct auditfilter_module *am)
{

	if (am->am_reinit == NULL)
		return (0);

	if (am->am_reinit(am, am->am_argc, am->am_argv) !=
	    AUDIT_FILTER_SUCCESS) {
		warnx("auditfilter_module_reinit: %s: failed",
		    am->am_modulename);
		return (-1);
	}

	return (0);
}