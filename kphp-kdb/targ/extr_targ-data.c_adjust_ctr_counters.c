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
struct advert {int l_views; int l_clicked_old; scalar_t__ g_clicked_old; scalar_t__ g_views; } ;

/* Variables and functions */
 int ADJ_VIEW_THRESHOLD ; 
 double INIT_L_CTR ; 

__attribute__((used)) static void adjust_ctr_counters (struct advert *A) {
  if (A->l_views >= 2*ADJ_VIEW_THRESHOLD && (double) A->l_clicked_old / A->l_views > 1.5*INIT_L_CTR) {
    int x = A->l_views / ADJ_VIEW_THRESHOLD;
    A->l_views /= x;
    A->l_clicked_old /= x;
  }
  A->g_views = 0;
  A->g_clicked_old = 0;
}