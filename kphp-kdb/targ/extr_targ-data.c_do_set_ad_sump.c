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
struct lev_targ_ad_setsump {long long sump0; long long sump1; long long sump2; } ;
struct advert {int flags; scalar_t__ price; int delta; int lambda; } ;

/* Variables and functions */
 int ADF_ANCIENT ; 
 int ESTIMATED_GAIN_EPS ; 
 int /*<<< orphan*/  LEV_TARG_AD_SETSUMP ; 
 scalar_t__ ad_became_ancient (struct advert*) ; 
 scalar_t__ alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 double compute_ad_lambda_delta (scalar_t__,long long,long long,long long,double*) ; 
 struct advert* get_ad_f (int,int /*<<< orphan*/ ) ; 
 int set_ad_sump (struct lev_targ_ad_setsump*) ; 

int do_set_ad_sump (int ad_id, long long g_sump0, long long g_sump1, long long g_sump2) {
  struct advert *A = get_ad_f (ad_id, 0);
  if (!A || (A->flags & ADF_ANCIENT) || ad_became_ancient (A) || g_sump0 < 0 || g_sump1 <= 0 || g_sump2 <= 0) {
    return 0; 
  }
  if (A->price <= 0) {
    return 1;
  }
  double f = 1.0 / (1LL << 32), new_delta;
  double new_lambda = compute_ad_lambda_delta (A->price, g_sump0 * f, g_sump1 * f, g_sump2 * f, &new_delta);
  if (new_delta >= (1 - ESTIMATED_GAIN_EPS) * A->delta && new_delta <= (1 + ESTIMATED_GAIN_EPS) * A->delta && new_lambda >= (1 - ESTIMATED_GAIN_EPS) * A->lambda && new_lambda <= (1 + ESTIMATED_GAIN_EPS) * A->lambda) {
    return 1;
  }
  struct lev_targ_ad_setsump *E = (struct lev_targ_ad_setsump *) alloc_log_event (LEV_TARG_AD_SETSUMP, 32, ad_id);
  E->sump0 = g_sump0;
  E->sump1 = g_sump1;
  E->sump2 = g_sump2;
  return set_ad_sump (E);
}