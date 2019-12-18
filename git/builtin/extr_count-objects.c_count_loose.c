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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ has_object_pack (struct object_id const*) ; 
 int /*<<< orphan*/  loose ; 
 int /*<<< orphan*/  loose_garbage (char const*) ; 
 int /*<<< orphan*/  loose_size ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 scalar_t__ on_disk_bytes (struct stat) ; 
 int /*<<< orphan*/  packed_loose ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int count_loose(const struct object_id *oid, const char *path, void *data)
{
	struct stat st;

	if (lstat(path, &st) || !S_ISREG(st.st_mode))
		loose_garbage(path);
	else {
		loose_size += on_disk_bytes(st);
		loose++;
		if (verbose && has_object_pack(oid))
			packed_loose++;
	}
	return 0;
}