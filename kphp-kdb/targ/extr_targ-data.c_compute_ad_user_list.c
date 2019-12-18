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
struct advert {int* user_list; int users; int /*<<< orphan*/  prev_user_creations; int /*<<< orphan*/  userlist_computed_at; int /*<<< orphan*/  flags; int /*<<< orphan*/  ad_id; int /*<<< orphan*/  query; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADF_PERIODIC ; 
 int /*<<< orphan*/  MAX_USERS ; 
 int /*<<< orphan*/  Q_limit ; 
 scalar_t__ Q_order ; 
 int /*<<< orphan*/  R ; 
 int R_cnt ; 
 int R_position ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ aux_userlist_tag ; 
 int /*<<< orphan*/  compile_query (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ global_birthday_in_query ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  now ; 
 int perform_query (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_lru_ads () ; 
 int /*<<< orphan*/  tot_userlists ; 
 int tot_userlists_size ; 
 int /*<<< orphan*/  user_creations ; 

__attribute__((used)) static int compute_ad_user_list (struct advert *A) {
  if (A->user_list) {
    tot_userlists--;
    tot_userlists_size -= A->users; 
    free (A->user_list);
    A->user_list = 0;
    A->users = 0;
  }

  process_lru_ads ();

  aux_userlist_tag = 0;

  assert (!compile_query (A->query));
  R_position = -1;
  Q_limit = MAX_USERS;
  Q_order = 0;
  global_birthday_in_query = 0;

  int res = perform_query (A->ad_id);
  R_position = 0;

  if (global_birthday_in_query) {
    A->flags |= ADF_PERIODIC;
  } else {
    A->flags &= ~ADF_PERIODIC;
  }

  assert (res >= 0 && res == R_cnt);

  A->users = res;
  
  A->user_list = malloc (res * 4 + 4);
  memcpy (A->user_list, R, res * 4);
  A->user_list[res] = 0x7fffffff;
  A->userlist_computed_at = now;
  A->prev_user_creations = user_creations;

  tot_userlists++;
  tot_userlists_size += res; 

  return res;
}