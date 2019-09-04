#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  d; int /*<<< orphan*/  photos; int /*<<< orphan*/  deleted_albums; int /*<<< orphan*/  album_by_photo; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  data_free_foreach ; 
 int /*<<< orphan*/  lookup_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_int_vptr_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_int_vptr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_free_changes (TYPE_1__*) ; 

void user_unloaded_free (user *u) {
  user_free_changes (u);

  lookup_free (&u->album_by_photo);
  set_int_free (&u->deleted_albums);
  map_int_vptr_foreach (&u->photos, data_free_foreach);
  map_int_vptr_free (&u->photos);
  data_free (&u->d);
}