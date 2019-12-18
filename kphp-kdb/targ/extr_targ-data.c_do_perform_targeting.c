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
struct lev_targ_target {int ad_price; int ad_query_len; int /*<<< orphan*/  ad_query; } ;
struct advert {int users; scalar_t__ query; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_TARGET ; 
 int MAX_QUERY_STRING_LEN ; 
 int /*<<< orphan*/  Qq ; 
 struct lev_targ_target* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ aux_userlist_tag ; 
 scalar_t__ compile_query (char*) ; 
 scalar_t__ do_ad_price_enable (int,int) ; 
 int do_ad_set_factor (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,char*) ; 
 struct advert* get_ad_f (int,int) ; 
 int load_ancient_ad (struct advert*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ perform_targeting (struct lev_targ_target*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int strlen (char*) ; 
 scalar_t__ verbosity ; 

int do_perform_targeting (int ad_id, int price, int factor, char *query) {
  struct advert *A = get_ad_f (ad_id, 1);
  int len = strlen (query);

  if (verbosity > 0) {
    fprintf (stderr, "in do_perform_targeting(%d,%d,%d,'%s'):\n", ad_id, price, factor, query);
  }

  int res = load_ancient_ad (A);
  if (res < 0) {
    return res;
  }

  aux_userlist_tag = 0;

  if (compile_query (query) || !Qq || !A || !price || ad_id <= 0 || len > MAX_QUERY_STRING_LEN) {
    return -1;
  }

  if (factor && (factor <= (int)1e5 || factor > (int)1e6)) {
    return -1;
  }

  if (A->query && !strcmp (A->query, query)) {
    assert (do_ad_price_enable (ad_id, price) >= 0);
    if (factor) {
      assert (do_ad_set_factor (ad_id, factor) == 1);
    }
    return A->users;
  }

  struct lev_targ_target *E = alloc_log_event (LEV_TARG_TARGET, 15 + len, ad_id);
  E->ad_price = price;
  E->ad_query_len = len;
  memcpy (E->ad_query, query, len + 1);

  assert (perform_targeting (E) >= 0);

  if (factor) {
    assert (do_ad_set_factor (ad_id, factor) == 1);
  }

  return A->users; 
}