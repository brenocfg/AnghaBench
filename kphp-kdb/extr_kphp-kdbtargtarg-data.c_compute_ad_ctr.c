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
struct advert {long long l_clicked_old; long long l_views; long long l_sump0; long long l_sump1; long long l_sump2; } ;

/* Variables and functions */
 struct advert* get_ad_f (int,int /*<<< orphan*/ ) ; 

int compute_ad_ctr (int ad_id, long long *res) {
  struct advert *A = get_ad_f (ad_id, 0);
  if (!A) { return 0; }
  res[0] = A->l_clicked_old;
  res[1] = A->l_views;
  res[2] = A->l_sump0 * (1LL << 32) + 0.5;
  res[3] = A->l_sump1 * (1LL << 32) + 0.5;
  res[4] = A->l_sump2 * (1LL << 32) + 0.5;
  return 5;
}