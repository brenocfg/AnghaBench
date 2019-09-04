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
typedef  int /*<<< orphan*/  object_id_t ;

/* Variables and functions */
 int last_metafile_start ; 
 int object_id_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int output_revlist_entries ; 
 int /*<<< orphan*/  tmp_object_id ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

void check_new_revlist_metafile_start (object_id_t object_id) {
  if (output_revlist_entries - last_metafile_start < 1000) {
    return;
  }
  int c = object_id_compare (tmp_object_id, object_id);
  if (c) {
    vkprintf (2, "New revlist metafile contains %lld items\n", output_revlist_entries - last_metafile_start);

    last_metafile_start = output_revlist_entries;
  }
}