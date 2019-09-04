#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
struct conv_attrs {TYPE_1__* drv; } ;
struct TYPE_2__ {int /*<<< orphan*/  required; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_CLEAN ; 
 int apply_filter (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_attrs (struct index_state const*,struct conv_attrs*,char const*) ; 

int would_convert_to_git_filter_fd(const struct index_state *istate, const char *path)
{
	struct conv_attrs ca;

	convert_attrs(istate, &ca, path);
	if (!ca.drv)
		return 0;

	/*
	 * Apply a filter to an fd only if the filter is required to succeed.
	 * We must die if the filter fails, because the original data before
	 * filtering is not available.
	 */
	if (!ca.drv->required)
		return 0;

	return apply_filter(path, NULL, 0, -1, NULL, ca.drv, CAP_CLEAN, NULL);
}