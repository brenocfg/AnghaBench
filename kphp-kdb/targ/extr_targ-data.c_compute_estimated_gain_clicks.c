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
struct advert {int ext_users; int users; long long price; } ;

/* Variables and functions */
 long long INIT_L_CLICKS ; 
 int INIT_L_VIEWS ; 
 int compute_projected_views (int) ; 
 int log_split_mod ; 

__attribute__((used)) static double compute_estimated_gain_clicks (struct advert *A, long long g_clicked, long long g_views) {
  int projected_l_views = INIT_L_VIEWS;
  if (A->ext_users) {
    projected_l_views = compute_projected_views (A->ext_users);
  } else if (A->users) {
    projected_l_views = compute_projected_views (A->users * log_split_mod);
  }
  return A->price * (g_clicked * 0.1 + INIT_L_CLICKS) / (g_views * 0.1 + projected_l_views);
}