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
struct TYPE_3__ {int metafile_len; int /*<<< orphan*/ * metafile; int /*<<< orphan*/  album_by_photo; int /*<<< orphan*/  d; int /*<<< orphan*/  photos; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/ * EMPTY__METAFILE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_data ; 
 int /*<<< orphan*/  data_unload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lookup_unload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_int_vptr_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_int_vptr_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * todel ; 
 int todel_n ; 
 int verbosity ; 

void unbind_user_metafile (user *u) {
  assert (u != NULL);

  if (verbosity > 2) {
    fprintf (stderr, "unbind_user_metafile\n");
  }
  todel_n = 0;
  map_int_vptr_foreach (&u->photos, check_data);
  int i;
  for (i = 0; i < todel_n; i++) {
    map_int_vptr_del (&u->photos, todel[i]);
  }

 // map_int_vptr_pack (&u->photos);

  data_unload (&u->d);
  lookup_unload (&u->album_by_photo);

  if (u->metafile != NULL && u->metafile != EMPTY__METAFILE) {
    dl_free (u->metafile, u->metafile_len);
  }

  u->metafile = NULL;
  u->metafile_len = -1;
}