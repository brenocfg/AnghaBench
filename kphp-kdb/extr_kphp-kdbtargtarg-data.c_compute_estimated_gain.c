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
struct advert {double price; int ext_users; int users; double expected_gain; double l_clicked_old; double g_clicked_old; double l_views; double g_views; } ;

/* Variables and functions */
 double INIT_L_CLICKS ; 
 int INIT_L_VIEWS ; 
 double MONEY_SCALE ; 
 double VIEW_GAIN_MULTIPLIER ; 
 int /*<<< orphan*/  compute_ad_lambda (struct advert*) ; 
 int compute_projected_views (int) ; 
 int log_split_mod ; 

double compute_estimated_gain (struct advert *A) {
  compute_ad_lambda (A);
  if (A->price > 0) {
    int projected_l_views = INIT_L_VIEWS;
    if (A->ext_users) {
      projected_l_views = compute_projected_views (A->ext_users);
    } else if (A->users) {
      projected_l_views = compute_projected_views (A->users * log_split_mod);
    }
    A->expected_gain = A->price * (A->l_clicked_old + A->g_clicked_old * 0.1 + INIT_L_CLICKS) / 
                                  (A->l_views + A->g_views * 0.1 + projected_l_views);
  } else {
    A->expected_gain = -1.0 * A->price * VIEW_GAIN_MULTIPLIER / MONEY_SCALE;
  }
  return A->expected_gain;
}