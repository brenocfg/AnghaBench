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
typedef  int /*<<< orphan*/  uint32_t ;
struct ext2fs_htree_entry {int /*<<< orphan*/  h_hash; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t
ext2_htree_get_hash(struct ext2fs_htree_entry *ep)
{
	return (ep->h_hash);
}