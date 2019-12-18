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
struct image_partition_entry {int /*<<< orphan*/ * data; } ;
struct device_info {int /*<<< orphan*/  support_trail; int /*<<< orphan*/  support_list; } ;

/* Variables and functions */
 struct image_partition_entry alloc_image_partition (char*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ *,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct image_partition_entry make_support_list(struct device_info *info) {
	size_t len = strlen(info->support_list);
	struct image_partition_entry entry = alloc_image_partition("support-list", len + 9);

	put32(entry.data, len);
	memset(entry.data+4, 0, 4);
	memcpy(entry.data+8, info->support_list, len);
	entry.data[len+8] = info->support_trail;

	return entry;
}