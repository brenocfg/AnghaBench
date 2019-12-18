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
struct advert {long long ad_id; long long flags; long long price; long long users; long long views; long long l_clicked; long long click_money; long long l_clicked_old; long long l_views; long long g_clicked_old; long long g_views; int expected_gain; long long ext_users; long long g_clicked; int l_sump0; int l_sump1; int l_sump2; int g_sump0; int g_sump1; int g_sump2; int lambda; int delta; long long recent_views; long long recent_views_limit; int factor; long long domain; long long group; long long category; long long subcategory; } ;

/* Variables and functions */
 struct advert* get_ad_f (int,int /*<<< orphan*/ ) ; 
 int sqrt (int) ; 

int compute_ad_info (int ad_id, long long *res) {
  struct advert *A = get_ad_f (ad_id, 0);
  if (!A) { return 0; }
  res[0] = A->ad_id;
  res[1] = A->flags;
  res[2] = A->price;
  res[3] = A->users;
  res[4] = A->views;
  res[5] = A->l_clicked;
  res[6] = A->click_money;
  res[7] = A->l_clicked_old;
  res[8] = A->l_views;
  res[9] = A->g_clicked_old;
  res[10] = A->g_views;
  res[11] = A->expected_gain * 1e9;
  res[12] = A->ext_users;
  res[13] = A->g_clicked;
  res[14] = A->l_sump0 * 1e9 + 0.5;
  res[15] = A->l_sump1 * 1e9 + 0.5;
  res[16] = A->l_sump2 * 1e9 + 0.5;
  res[17] = A->g_sump0 * 1e9 + 0.5;
  res[18] = A->g_sump1 * 1e9 + 0.5;
  res[19] = A->g_sump2 * 1e9 + 0.5;
  if (A->price > 0) {
    res[20] = (A->lambda / A->price) * 1e9;
    res[21] = (A->delta / A->price) * (1e9 / sqrt (3));
  } else {
    res[20] = res[21] = 0;
  }
  res[22] = A->recent_views;
  res[23] = A->recent_views_limit;
  res[24] = A->factor * 1e6 + 0.5;
  res[25] = A->domain;
  res[26] = A->group;
  res[27] = A->category;
  res[28] = A->subcategory;
  return 29;
}