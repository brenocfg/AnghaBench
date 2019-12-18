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
struct repository {int dummy; } ;
struct oid_array {int dummy; } ;
struct diff_filespec {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; scalar_t__ oid_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_INFO_FOR_PREFETCH ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,int /*<<< orphan*/ *) ; 
 scalar_t__ oid_object_info_extended (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_if_missing(struct repository *r,
			   struct oid_array *to_fetch,
			   const struct diff_filespec *filespec)
{
	if (filespec && filespec->oid_valid &&
	    !S_ISGITLINK(filespec->mode) &&
	    oid_object_info_extended(r, &filespec->oid, NULL,
				     OBJECT_INFO_FOR_PREFETCH))
		oid_array_append(to_fetch, &filespec->oid);
}