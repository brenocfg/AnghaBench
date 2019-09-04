#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  h; } ;
struct TYPE_10__ {TYPE_1__ to; } ;
struct TYPE_9__ {int metafile; int metafile_len; int types_cnt; char* known_types; long long* object_type_ids; int object_old_n; TYPE_4__ object_table; int /*<<< orphan*/  object_chg; int /*<<< orphan*/ * object_old_ratings; int /*<<< orphan*/  load_time; } ;
typedef  TYPE_2__ user ;
typedef  int /*<<< orphan*/  rating ;
struct TYPE_11__ {int has_crc32; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHG_INIT (int /*<<< orphan*/ ) ; 
 int EMPTY__METAFILE ; 
 int /*<<< orphan*/  READ_INT (char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crc32_check_and_repair (int,int,unsigned int*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__ header ; 
 int /*<<< orphan*/  ltbl_set_size (TYPE_4__*,int) ; 
 int /*<<< orphan*/  now ; 
 int rating_num ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_2__* users ; 
 int verbosity ; 

void bind_user_metafile (user *u) {
  u->load_time = now;
  if (verbosity > 2) {
    fprintf (stderr, "bind user metafile local id = %d (%p), hash (%p)\n", (int)(u - users), u, u->object_table.to.h);
  }

#ifdef HINTS
  int pref_n = 0;
  change_list_ptr temp = u->chg_list_st;
  while (temp->next != NULL) {
    temp = temp->next;
    if (temp->x > 0) {
      pref_n++;
    }
  }

  pref_n *= 15;
  if (verbosity > 2) {
    fprintf (stderr, "pref_n = %d\n", pref_n);
  }

  int htbl_size = pref_n * 1.25;
  if (htbl_size < 100) {
    htbl_size = 100;
  }
  htbl_set_size (&u->pref_table, htbl_size);
#endif

  if (u->metafile == EMPTY__METAFILE) {
#ifdef HINTS
    u->mtf_i = NULL;
    u->mtf_h = NULL;
    u->mtf_n = 0;
#endif
    return;
  }

  if (header.has_crc32) {
    crc32_check_and_repair (u->metafile, u->metafile_len - sizeof (unsigned int), (unsigned int *)(u->metafile + u->metafile_len - sizeof (unsigned int)), 1);
  }

#ifdef HINTS
  int pref_metafile_len;
  READ_INT (u->metafile, pref_metafile_len);
#endif
  char *s = u->metafile, *t = u->metafile;

#ifdef HINTS
  u->mtf_n = ((int *)t)[0];
  u->mtf_h = (void *)(t + sizeof (int));

  if (header.perf_hash) {
    t += sizeof (int) + sizeof (short) * u->mtf_n;
    ph_init (&u->h);
    t += ph_decode (&u->h, (unsigned char *)t);
  } else {
    t += sizeof (int) + sizeof (long long) * u->mtf_n;
  }
#endif

  READ_INT(t, u->types_cnt);
  u->known_types = t;
  t += (sizeof (int) + sizeof (char)) * u->types_cnt;

#ifdef HINTS
  u->mtf_i = (int *)t;

  s += pref_metafile_len;

  if (verbosity > 2) {
    int n = u->mtf_n;
    fprintf (stderr, "Number of hashes = %d, size of golomb codes = %d\n", 12 * n,
      u->mtf_i[n] - u->mtf_i[0]);
  }
#else
  s = t;
#endif

  // read objects ids
  int object_n, t_object_n;
  READ_INT(s, object_n);

  u->object_type_ids = (long long *)s;
#ifdef HINTS
  u->object_indexes = (int *)(u->object_type_ids + (object_n + 1));
  u->object_old_ratings = (rating *)(u->object_indexes + (object_n + 1));
  u->object_data = (char *)(u->object_old_ratings + (object_n + 1) * rating_num);

  if (verbosity > 2) {
    fprintf (stderr, "Number of objects = %d, size of objects names = %d\n", 16 * object_n,
      u->object_indexes[object_n]-u->object_indexes[1]);
  }
#else
  u->object_old_ratings = (rating *)(u->object_type_ids + (object_n + 1));
  assert (u->metafile_len == (int)((sizeof (int) + sizeof (char)) * u->types_cnt + 2 * sizeof (int) +
                                   (sizeof (rating) * rating_num + sizeof (long long)) * (object_n + 1) +
                                    sizeof (unsigned int) * header.has_crc32));
  CHG_INIT (u->object_chg);
#endif
  u->object_old_n = object_n;

  t_object_n = 100;
  if (t_object_n < 100) {
    t_object_n = 100;
  }

  ltbl_set_size (&u->object_table, t_object_n);
}