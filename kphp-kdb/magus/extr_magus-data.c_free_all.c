#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user ;
struct TYPE_6__ {int objs_limit; scalar_t__ file_type; int total_scores; int has_names; int fid_names_cnt; int /*<<< orphan*/  fid_id; int /*<<< orphan*/  fid_id_str; TYPE_2__* fid_names_begins; TYPE_2__* fid_names; TYPE_2__* C; TYPE_2__* C_index; TYPE_2__* CC; TYPE_2__* f_mul; int /*<<< orphan*/  fids; } ;
typedef  TYPE_1__ similarity_index_header ;
typedef  int /*<<< orphan*/  score ;
struct TYPE_7__ {int /*<<< orphan*/  new_exceptions; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dl_free (TYPE_2__*,int) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  dl_strfree (TYPE_2__) ; 
 scalar_t__* dumps ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  free_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h_users ; 
 int /*<<< orphan*/  header ; 
 int /*<<< orphan*/  hset_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hset_intp_free (int /*<<< orphan*/ *) ; 
 int index_mode ; 
 int /*<<< orphan*/  map_int_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_string_int_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* sim_header ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__* types ; 
 int user_LRU_unload () ; 
 int user_cnt ; 
 TYPE_2__* users ; 
 int /*<<< orphan*/  vector_int_free (int /*<<< orphan*/ *) ; 
 scalar_t__ verbosity ; 

void free_all (void) {
  if (verbosity > 0) {
    while (user_LRU_unload() != -1) {
    }

    int i, j;
    for (i = 0; i < user_cnt; i++) {
      hset_int_free (&users[i].new_exceptions);
    }

    for (i = 1; i < 256; i++) {
      if (types[i]) {
        similarity_index_header *header = &sim_header[i];
        int fn = header->objs_limit;

        vector_int_free (&header->fids);

        dl_free (header->f_mul, sizeof (float) * fn);

        if (header->file_type == 0) {
          dl_free (header->CC, sizeof (float) * header->total_scores);
        } else {
          dl_free (header->C_index, sizeof (int) * (fn + 1));
          dl_free (header->C, sizeof (score) * header->total_scores);
        }

        if (header->has_names) {
          dl_free (header->fid_names, header->has_names);

          for (j = fn; j < header->fid_names_cnt; j++) {
            dl_strfree (header->fid_names_begins[j]);
          }
          dl_free (header->fid_names_begins, sizeof (char *) * (fn * (index_mode + 1) + 1024000 * index_mode + 1));
          map_string_int_free (&header->fid_id_str);
        } else {
          map_int_int_free (&header->fid_id);
        }
      }
      if (dumps[i]) {
//        vector_free (obj_scores[i]);
      }
    }

    dl_free (users, sizeof (user) * user_cnt);

    hset_intp_free (&h_users);
    free_header (&header);

    fprintf (stderr, "Memory left: %lld\n", dl_get_memory_used());
    assert (dl_get_memory_used() == 0);
  }
}