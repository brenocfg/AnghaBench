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
struct untracked_cache_dir {scalar_t__ untracked_nr; scalar_t__ valid; } ;
struct untracked_cache {int /*<<< orphan*/  dir_invalidated; } ;

/* Variables and functions */

__attribute__((used)) static void invalidate_one_directory(struct untracked_cache *uc,
				     struct untracked_cache_dir *ucd)
{
	uc->dir_invalidated++;
	ucd->valid = 0;
	ucd->untracked_nr = 0;
}