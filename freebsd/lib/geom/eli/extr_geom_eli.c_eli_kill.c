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
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eli_is_attached (char const*) ; 
 int /*<<< orphan*/  eli_kill_detached (struct gctl_req*,char const*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*,int) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  gctl_issue (struct gctl_req*) ; 

__attribute__((used)) static void
eli_kill(struct gctl_req *req)
{
	const char *prov;
	int i, nargs, all;

	nargs = gctl_get_int(req, "nargs");
	all = gctl_get_int(req, "all");
	if (!all && nargs == 0) {
		gctl_error(req, "Too few arguments.");
		return;
	}
	/*
	 * How '-a' option combine with a list of providers:
	 * Delete Master Keys from all attached providers:
	 * geli kill -a
	 * Delete Master Keys from all attached providers and from
	 * detached da0 and da1:
	 * geli kill -a da0 da1
	 * Delete Master Keys from (attached or detached) da0 and da1:
	 * geli kill da0 da1
	 */

	/* First detached providers. */
	for (i = 0; i < nargs; i++) {
		prov = gctl_get_ascii(req, "arg%d", i);
		if (!eli_is_attached(prov))
			eli_kill_detached(req, prov);
	}
	/* Now attached providers. */
	gctl_issue(req);
}