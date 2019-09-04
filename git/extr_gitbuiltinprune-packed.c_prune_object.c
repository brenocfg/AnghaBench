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
struct object_id {int dummy; } ;

/* Variables and functions */
 int PRUNE_PACKED_DRY_RUN ; 
 int /*<<< orphan*/  has_object_pack (struct object_id const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  unlink_or_warn (char const*) ; 

__attribute__((used)) static int prune_object(const struct object_id *oid, const char *path,
			 void *data)
{
	int *opts = data;

	if (!has_object_pack(oid))
		return 0;

	if (*opts & PRUNE_PACKED_DRY_RUN)
		printf("rm -f %s\n", path);
	else
		unlink_or_warn(path);
	return 0;
}