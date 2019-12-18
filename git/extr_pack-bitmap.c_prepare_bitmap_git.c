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
struct bitmap_index {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_bitmap_index (struct bitmap_index*) ; 
 int /*<<< orphan*/  load_pack_bitmap (struct bitmap_index*) ; 
 int /*<<< orphan*/  open_pack_bitmap (struct repository*,struct bitmap_index*) ; 
 struct bitmap_index* xcalloc (int,int) ; 

struct bitmap_index *prepare_bitmap_git(struct repository *r)
{
	struct bitmap_index *bitmap_git = xcalloc(1, sizeof(*bitmap_git));

	if (!open_pack_bitmap(r, bitmap_git) && !load_pack_bitmap(bitmap_git))
		return bitmap_git;

	free_bitmap_index(bitmap_git);
	return NULL;
}