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
typedef  int /*<<< orphan*/  rating ;

/* Variables and functions */
 int MAX_CNT ; 
 size_t MAX_HISTORY ; 
 int MAX_K ; 
 int MAX_RATING_NUM ; 
 int MAX_USR_SIZE ; 
 int /*<<< orphan*/  allocated_metafile_bytes ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buff ; 
 int /*<<< orphan*/  buffer ; 
 scalar_t__ changes_memory ; 
 scalar_t__ chg_list_get_memory () ; 
 int /*<<< orphan*/  d ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dl_strfree (scalar_t__) ; 
 int /*<<< orphan*/ * dp ; 
 int /*<<< orphan*/  exc ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long,...) ; 
 int /*<<< orphan*/  free_header (int /*<<< orphan*/ *) ; 
 scalar_t__ get_changes_memory () ; 
 scalar_t__ get_memory_used () ; 
 int /*<<< orphan*/  h_buff ; 
 int /*<<< orphan*/  header ; 
 int /*<<< orphan*/  heap ; 
 size_t history_l ; 
 scalar_t__* history_q ; 
 size_t history_r ; 
 scalar_t__ htbl_get_memory () ; 
 scalar_t__ htbl_vct_get_memory () ; 
 int /*<<< orphan*/  i_buff ; 
 scalar_t__ index_mode ; 
 int /*<<< orphan*/  intersect_buff ; 
 int /*<<< orphan*/  ltbl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_h ; 
 int /*<<< orphan*/  new_obj ; 
 int /*<<< orphan*/  object_buf ; 
 int /*<<< orphan*/  object_indexes ; 
 int /*<<< orphan*/  object_ratings ; 
 int /*<<< orphan*/  object_ratings_to_sort ; 
 int /*<<< orphan*/  objects_to_sort ; 
 int /*<<< orphan*/  objects_typeids_to_sort ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ trp_get_memory () ; 
 int /*<<< orphan*/  type_ids ; 
 int user_LRU_unload () ; 
 int /*<<< orphan*/  user_table ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  weight ; 

void free_all (void) {
  if (verbosity) {
    while (user_LRU_unload() != -1) {
    }

    while (history_l != history_r) {
      dl_strfree (history_q[history_l]);
      history_q[history_l++] = 0;
      if (history_l > MAX_HISTORY) {
        history_l = 0;
      }
    }

    fprintf (stderr, "Memory left : %ld\n", (long)(get_memory_used() - trp_get_memory() - htbl_get_memory() - htbl_vct_get_memory() -
             changes_memory - chg_list_get_memory()));
    fprintf (stderr, "memory used = %ld, trp_memory = %ld, htbl_memory = %ld, changes_memory = %ld, mtf = %lld, vct = %ld\n",
             get_memory_used(), (long)trp_get_memory(), (long)htbl_get_memory(), (long)get_changes_memory(), allocated_metafile_bytes, (long)htbl_vct_get_memory());

    assert ((long)(get_memory_used() - trp_get_memory() - htbl_get_memory() - htbl_vct_get_memory() -
                   changes_memory - chg_list_get_memory()) == 0);

    dl_free (buff, (MAX_CNT + 1) * sizeof (int));

    if (index_mode) {
      dl_free (buffer, MAX_USR_SIZE);
      dl_free (new_obj, MAX_USR_SIZE);
      dl_free (type_ids, (MAX_CNT + 1) * sizeof (long long));
      dl_free (object_ratings, (MAX_CNT + 1) * sizeof (rating) * MAX_RATING_NUM);
      dl_free (object_ratings_to_sort, (MAX_CNT + 1) * sizeof (rating));
      dl_free (h_buff, MAX_USR_SIZE);

#ifdef HINTS
      dl_free (i_buff, MAX_USR_SIZE);
      dl_free (new_h, MAX_USR_SIZE);
      dl_free (object_indexes, (MAX_CNT + 1) * sizeof (int));
      dl_free (object_buf, MAX_USR_SIZE);
#endif
    } else {
      int i;
      for (i = 0; i <= MAX_K; i++) {
        dl_free (dp[i], (MAX_CNT + 1) * sizeof (rating));
      }
      dl_free (d, (MAX_CNT + 1) * sizeof (rating));
      dl_free (weight, MAX_CNT * sizeof (rating));

      dl_free (heap, (MAX_CNT + 1) * sizeof (int));
      dl_free (objects_typeids_to_sort, MAX_CNT * sizeof (long long));
      dl_free (objects_to_sort, MAX_CNT * sizeof (int));

#ifdef HINTS
      dl_free (intersect_buff, (MAX_CNT + 1) * sizeof (int));
#else
      dl_free (exc, (MAX_CNT + 1) * sizeof (int));
#endif
    }

    ltbl_free (&user_table);
    free_header (&header);
  }
}