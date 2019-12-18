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
struct diff_filespec {int /*<<< orphan*/  oid; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  oid_valid; } ;

/* Variables and functions */
 scalar_t__ diff_populate_filespec (struct repository*,struct diff_filespec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 unsigned int oidhash (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int hash_filespec(struct repository *r,
				  struct diff_filespec *filespec)
{
	if (!filespec->oid_valid) {
		if (diff_populate_filespec(r, filespec, 0))
			return 0;
		hash_object_file(filespec->data, filespec->size, "blob",
				 &filespec->oid);
	}
	return oidhash(&filespec->oid);
}