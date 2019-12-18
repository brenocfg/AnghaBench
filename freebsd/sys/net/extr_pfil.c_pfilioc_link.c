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
struct pfilioc_link {int pio_flags; int /*<<< orphan*/  pio_ruleset; int /*<<< orphan*/  pio_module; int /*<<< orphan*/  pio_name; } ;
struct pfil_link_args {int pa_flags; int /*<<< orphan*/  pa_rulname; int /*<<< orphan*/  pa_modname; int /*<<< orphan*/  pa_headname; int /*<<< orphan*/  pa_version; } ;

/* Variables and functions */
 int EINVAL ; 
 int PFIL_APPEND ; 
 int PFIL_IN ; 
 int PFIL_OUT ; 
 int PFIL_UNLINK ; 
 int /*<<< orphan*/  PFIL_VERSION ; 
 int pfil_link (struct pfil_link_args*) ; 

__attribute__((used)) static int
pfilioc_link(struct pfilioc_link *req)
{
	struct pfil_link_args args;

	if (req->pio_flags & ~(PFIL_IN | PFIL_OUT | PFIL_UNLINK | PFIL_APPEND))
		return (EINVAL);

	args.pa_version = PFIL_VERSION;
	args.pa_flags = req->pio_flags;
	args.pa_headname = req->pio_name;
	args.pa_modname = req->pio_module;
	args.pa_rulname = req->pio_ruleset;

	return (pfil_link(&args));
}