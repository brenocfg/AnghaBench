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
struct remote {int /*<<< orphan*/  fetch; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 char* apply_refspecs (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ read_ref (char*,struct object_id*) ; 

__attribute__((used)) static int remote_tracking(struct remote *remote, const char *refname,
			   struct object_id *oid)
{
	char *dst;

	dst = apply_refspecs(&remote->fetch, refname);
	if (!dst)
		return -1; /* no tracking ref for refname at remote */
	if (read_ref(dst, oid))
		return -1; /* we know what the tracking ref is but we cannot read it */
	return 0;
}