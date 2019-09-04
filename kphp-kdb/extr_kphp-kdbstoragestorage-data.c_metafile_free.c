#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  local_id; TYPE_1__* B; } ;
typedef  TYPE_2__ metafile_t ;
struct TYPE_7__ {int /*<<< orphan*/  volume_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_use (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/ * get_meta_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  metafiles_unloaded ; 
 int /*<<< orphan*/  vkprintf (int,char*,TYPE_2__*) ; 

__attribute__((used)) static void metafile_free (metafile_t *meta) {
  int h;
  vkprintf (3, "metafile_free (%p)\n", meta);
  del_use (meta);
  assert (get_meta_f (meta->B->volume_id, meta->local_id, &h, -1) != NULL);
  free (meta);
  metafiles_unloaded++;
}