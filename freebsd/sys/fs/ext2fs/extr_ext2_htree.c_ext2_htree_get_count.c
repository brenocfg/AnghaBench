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
typedef  int /*<<< orphan*/  uint16_t ;
struct ext2fs_htree_entry {int dummy; } ;
struct ext2fs_htree_count {int /*<<< orphan*/  h_entries_num; } ;

/* Variables and functions */

__attribute__((used)) static uint16_t
ext2_htree_get_count(struct ext2fs_htree_entry *ep)
{
	return (((struct ext2fs_htree_count *)(ep))->h_entries_num);
}