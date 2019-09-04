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
struct advert {long users; int /*<<< orphan*/ * user_list; } ;

/* Variables and functions */
 int ADF_SITES_MASK_SHIFT ; 
 int Q_limit ; 
 int /*<<< orphan*/ * R ; 
 int R_cnt ; 
 int __and_mask ; 
 long long __cat_mask ; 
 int __exclude_ad_id ; 
 int __use_factor ; 
 scalar_t__ __use_views_limit ; 
 int __xor_mask ; 
 struct advert* get_ad_f (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_push_user_ad ; 
 int /*<<< orphan*/  heap_push_user_ad_ext ; 
 int /*<<< orphan*/  heap_push_user_ad_std ; 
 long lrand48 () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int user_ad_price (int /*<<< orphan*/ ,int) ; 

int perform_ad_pricing (int ad_id, int position, int flags, int and_mask, int xor_mask, int max_users) {
  R_cnt = 0;
  if (ad_id <= 0 || position <= 0 || position > 100 || max_users <= 0 || max_users > 1000) { 
    return -1; 
  }
  struct advert *A = get_ad_f (ad_id, 0);
  if (!A || !A->user_list) {
    return -1;
  }

  if (Q_limit <= 0) {
    Q_limit = 1000;
  }
  if (Q_limit > 10000) {
    Q_limit = 10000;
  }
  memset (R, 0, Q_limit * sizeof(int));

  heap_push_user_ad = (flags & 8) ? heap_push_user_ad_ext : heap_push_user_ad_std;
  __use_factor = 1;
  __use_views_limit = 0;
  __exclude_ad_id = ad_id;
  __and_mask = (and_mask & 0xff) << ADF_SITES_MASK_SHIFT;
  __xor_mask = (xor_mask & 0xff) << ADF_SITES_MASK_SHIFT;
  __cat_mask = -1LL;

  long i, N = A->users;
  if (max_users > N) {
    max_users = N;
  }
  long M = max_users;
  for (i = 0; i < A->users; i++) {
    if (lrand48() % N < M) {
      M--;
      int r = user_ad_price (A->user_list[i], position);
      if (r >= Q_limit) {
	r = Q_limit - 1;
      } else if (r < 0) {
	r = 0;
      }
      R[r]++;
    }
    N--;
  }
  __use_factor = 0;
  __use_views_limit = 0;
  __exclude_ad_id = 0;
  __and_mask = (254 << ADF_SITES_MASK_SHIFT);
  __xor_mask = 0;

  R_cnt = Q_limit; 
  while (R_cnt && !R[R_cnt-1]) { R_cnt--; }
  return max_users;
}