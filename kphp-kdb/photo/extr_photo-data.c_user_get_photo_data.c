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
struct TYPE_4__ {int albums_n; scalar_t__* albums_offset; scalar_t__ metafile; int /*<<< orphan*/  albums_id; int /*<<< orphan*/  deleted_albums; int /*<<< orphan*/  photos; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 scalar_t__ EMPTY__METAFILE ; 
 scalar_t__ EMPTY__METAFILE_LEN ; 
 int data_get_local_id_by_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  data_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  data_load (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  data_loaded (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int dl_find_int (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * dl_malloc (int) ; 
 scalar_t__ map_int_vptr_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  photo_func ; 
 int /*<<< orphan*/ * set_int_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * user_get_album_data (TYPE_1__*) ; 

data *user_get_photo_data (user *u, int aid) {
//  dbg ("user_get_photo_data %d: album_id = %d\n", u->id, aid);

  data *albums = user_get_album_data (u);

  int lid = data_get_local_id_by_id (albums, aid);
  if (lid == -1) {
    dbg ("unexisted album %d\n", aid);
    return NULL;
  }

  data **d = (data **)map_int_vptr_add (&u->photos, aid);
  if (*d == NULL) {
    *d = dl_malloc (sizeof (data));
    data_init (*d, &photo_func);
  }

//  dbg ("load data if needed\n");

  if (!data_loaded (*d)) {
    int i = u->albums_n;
    if (set_int_get (&u->deleted_albums, aid) == NULL) {
      i = dl_find_int (u->albums_id, u->albums_n, aid);
    }
    if (i != u->albums_n) {
      data_load (*d, u->metafile + u->albums_offset[i], u->albums_offset[i + 1] - u->albums_offset[i]);
    } else {
      data_load (*d, EMPTY__METAFILE, EMPTY__METAFILE_LEN);
    }
  }

  return *d;
}