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
typedef  int /*<<< orphan*/  tdata ;
typedef  int /*<<< orphan*/  rating ;
typedef  int /*<<< orphan*/  q_info ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int STAT_ST ; 
 int /*<<< orphan*/  aho_black_list ; 
 int aho_black_list_size ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  h_id ; 
 int /*<<< orphan*/  h_pref ; 
 int /*<<< orphan*/  h_q ; 
 int /*<<< orphan*/  h_word ; 
 int /*<<< orphan*/  hmap_ll_int_free (int /*<<< orphan*/ *) ; 
 int idr ; 
 int /*<<< orphan*/  names ; 
 int /*<<< orphan*/  names_buff ; 
 int namesr ; 
 int prefr ; 
 int /*<<< orphan*/  q_entry ; 
 int /*<<< orphan*/  q_rev ; 
 int qr ; 
 int /*<<< orphan*/  ratings ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stemmed_names ; 
 int /*<<< orphan*/  suggs ; 
 scalar_t__ verbosity ; 
 int wordr ; 
 int /*<<< orphan*/  words ; 

void free_all (void) {
  if (verbosity) {
#ifdef TYPES
    dl_free (words, wordr * sizeof (tdata));
    hmap_ll_int_free (&h_word);
#endif

    dl_free (suggs, prefr * sizeof (data));
    dl_free (ratings, idr * sizeof (rating));
    dl_free (names, idr * sizeof (int));
    dl_free (stemmed_names, idr * sizeof (int));
    dl_free (names_buff, namesr * sizeof (char));
    dl_free (q_entry, (qr + STAT_ST) * sizeof (q_info));
    dl_free (q_rev, qr * sizeof (int));

    hmap_ll_int_free (&h_pref);
    hmap_ll_int_free (&h_id);
    hmap_ll_int_free (&h_q);

    dl_free (aho_black_list, aho_black_list_size);

    fprintf (stderr, "Memory left: %lld\n", dl_get_memory_used());
    assert (dl_get_memory_used() == 0);
  }
}