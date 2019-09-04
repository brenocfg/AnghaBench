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
struct TYPE_3__ {int load_time; int object_size; int metafile_len; scalar_t__ object_old_n; int /*<<< orphan*/ * object_type_ids; int /*<<< orphan*/ * metafile; int /*<<< orphan*/ * prev_used; int /*<<< orphan*/ * next_used; int /*<<< orphan*/  object_table; int /*<<< orphan*/ * object_ratings; int /*<<< orphan*/  object_chg; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  rating ;

/* Variables and functions */
 int /*<<< orphan*/ * EMPTY__METAFILE ; 
 int /*<<< orphan*/  chg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ltbl_free (int /*<<< orphan*/ *) ; 
 int max_cache_time ; 
 int min_cache_time ; 
 int now ; 
 int rating_num ; 
 int /*<<< orphan*/  stderr ; 
 int total_cache_time ; 
 int verbosity ; 

void unbind_user_metafile (user *u) {
  if (u == NULL) {
    return;
  }
  int cache_time = now - u->load_time;
  total_cache_time += cache_time;
  if (cache_time > max_cache_time) {
    max_cache_time = cache_time;
  }
  if (cache_time < min_cache_time) {
    min_cache_time = cache_time;
  }

  if (verbosity > 2) {
    fprintf (stderr, "unbind_user_metafile\n");
  }

  dl_free (u->object_ratings, u->object_size * sizeof (rating) * rating_num);

#ifdef HINTS
  int i;
  for (i = 1; i < u->object_table.currId; i++) {
    if (u->object_names[i] != NULL) {
      dl_free (u->object_names[i], (strlen (u->object_names[i]) + 1) * sizeof (char));
    }
  }
  dl_free (u->object_names, u->object_size * sizeof (char *));

  for (i = 0; i < u->changed_objs.n; i++) {
    char *s = *((char **)(u->object_data + (u->object_indexes[u->changed_objs.mem[i]] & ~MEM_FLAG)));
    if (s != NULL) {
      dl_free (s, (strlen (s) + 1) * sizeof (char));
    }
  }
  vct_free (&u->changed_objs);

  u->object_names = NULL;
  htbl_free (&u->pref_table);
#else
  chg_free (&u->object_chg);
#endif

  u->object_size = 0;
  u->object_ratings = NULL;

  ltbl_free (&u->object_table);

  u->next_used = NULL;
  u->prev_used = NULL;

  if (u->metafile != EMPTY__METAFILE) {
#ifdef HINTS
    dl_free (u->metafile - sizeof (int), u->metafile_len);
#else
    dl_free (u->metafile, u->metafile_len);
#endif
  }

  u->metafile = NULL;
  u->metafile_len = 0;
#ifdef HINTS
  u->mtf_i = NULL;
  u->mtf_h = NULL;
  u->mtf_n = 0;

  u->object_data = NULL;
  u->object_indexes = NULL;
#endif
  u->object_type_ids = NULL;
  u->object_old_n = 0;
}