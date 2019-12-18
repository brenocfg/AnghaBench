#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int metafile_len; int /*<<< orphan*/  deleted_albums; int /*<<< orphan*/  photos; int /*<<< orphan*/  album_by_photo; int /*<<< orphan*/  d; int /*<<< orphan*/ * prev_used; int /*<<< orphan*/ * next_used; int /*<<< orphan*/ * aio; int /*<<< orphan*/ * metafile; scalar_t__ local_id; scalar_t__ id; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  data_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lookup_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_int_vptr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  photo_func ; 
 int /*<<< orphan*/  set_int_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_only ; 

void user_init (user *u) {
  u->id = 0;
  u->local_id = 0;
  u->metafile = NULL;
  u->metafile_len = -1;

  u->aio = NULL;
  u->next_used = NULL;
  u->prev_used = NULL;

  if (!write_only) {
    data_init (&u->d, &photo_func);
    lookup_init (&u->album_by_photo);
    map_int_vptr_init (&u->photos);
    set_int_init (&u->deleted_albums);
  }
}