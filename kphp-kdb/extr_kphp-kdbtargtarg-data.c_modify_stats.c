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
struct lev_targ_stat_load {scalar_t__ clicked; int click_money; scalar_t__ views; scalar_t__ l_clicked; scalar_t__ l_views; } ;
struct advert {scalar_t__ l_clicked; scalar_t__ views; int click_money; scalar_t__ l_clicked_old; scalar_t__ l_views; int /*<<< orphan*/  flags; scalar_t__ l_sump2; scalar_t__ l_sump1; scalar_t__ l_sump0; int /*<<< orphan*/  g_sump2; int /*<<< orphan*/  g_sump1; int /*<<< orphan*/  g_sump0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADF_ANYVIEWS ; 
 int MONEY_SCALE ; 
 int /*<<< orphan*/  compute_estimated_gain (struct advert*) ; 
 int tot_click_money ; 
 scalar_t__ tot_clicks ; 
 scalar_t__ tot_views ; 
 int /*<<< orphan*/  total_sump0 ; 
 int /*<<< orphan*/  total_sump1 ; 
 int /*<<< orphan*/  total_sump2 ; 

__attribute__((used)) static int modify_stats (struct lev_targ_stat_load *E, struct advert *A) {
  tot_clicks -= A->l_clicked;
  tot_views -= A->views;
  tot_click_money -= A->click_money;

  A->l_clicked = E->clicked > 0 ? E->clicked : 0;
  A->click_money = E->click_money > 0 ? E->click_money * MONEY_SCALE : 0;
  A->views = E->views > 0 ? E->views : 0;
  A->l_clicked_old = E->l_clicked > 0 ? E->l_clicked : 0;
  A->l_views = E->l_views > 0 ? E->l_views : 0;

  tot_clicks += A->l_clicked;
  tot_views += A->views;
  tot_click_money += A->click_money;
  
  total_sump0 -= A->l_sump0;
  total_sump1 -= A->l_sump1;
  total_sump2 -= A->l_sump2;
  A->g_sump0 -= A->l_sump0;
  A->g_sump1 -= A->l_sump1;
  A->g_sump2 -= A->l_sump2;
  A->l_sump0 = 0;
  A->l_sump1 = 0;
  A->l_sump2 = 0;
  A->flags &= ~ADF_ANYVIEWS;
  compute_estimated_gain (A);

  return 0;
}