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
struct lev_start {scalar_t__ schema_id; scalar_t__ split_min; scalar_t__ split_max; scalar_t__ split_mod; } ;

/* Variables and functions */
 scalar_t__ TEXT_SCHEMA_V1 ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ log_split_max ; 
 scalar_t__ log_split_min ; 
 scalar_t__ log_split_mod ; 

__attribute__((used)) static int text_le_start (struct lev_start *E) {
  if (E->schema_id != TEXT_SCHEMA_V1) {
    return -1;
  }
  log_split_min = E->split_min;
  log_split_max = E->split_max;
  log_split_mod = E->split_mod;
  assert (log_split_mod > 0 && log_split_min >= 0 && log_split_min + 1 == log_split_max && log_split_max <= log_split_mod);

/*
  int q = 0;
  if (E->extra_bytes >= 3 && E->str[0] == 1) {
    init_extra_mask (*(unsigned short *) (E->str + 1));
    q = 3;
  }
  if (E->extra_bytes >= q + 6 && !memcmp (E->str + q, "status", 6)) {
    memcpy (&PeerFlagFilter, &Statuses_PeerFlagFilter, sizeof (PeerFlagFilter));
    Sublists = Statuses_Sublists;
    count_sublists ();
  }
  if (E->extra_bytes >= q + 5 && !memcmp (E->str + q, "forum", 5)) {
    memcpy (&PeerFlagFilter, &Forum_PeerFlagFilter, sizeof (PeerFlagFilter));
    Sublists = Forum_Sublists;
    count_sublists ();
  }
*/  

  return 0;
}