#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_5__* uplink; } ;
typedef  TYPE_1__ utree_t ;
struct TYPE_18__ {int sex; int operator; int browser; int region; int height; int smoking; int alcohol; int ppriority; int iiothers; int hidden; int cvisited; int gcountry; int custom1; int custom2; int custom3; int custom4; int custom5; int custom6; int custom7; int custom8; int custom9; int custom10; int custom11; int custom12; int custom13; int custom14; int custom15; int timezone; int has_photo; int mstatus; int political; int uni_country; int uni_city; int bday_year; int bday_month; int bday_day; int /*<<< orphan*/ * weights; int /*<<< orphan*/  clicked_ads; int /*<<< orphan*/  inactive_ads; int /*<<< orphan*/  active_ads; scalar_t__ name; scalar_t__ proposal; scalar_t__ hometown; scalar_t__ religion; int /*<<< orphan*/  uid; int /*<<< orphan*/  proposal_hashes; int /*<<< orphan*/  hometown_hashes; int /*<<< orphan*/  religion_hashes; int /*<<< orphan*/  name_hashes; TYPE_5__* right_rate; TYPE_5__* left_rate; TYPE_5__* uplink_rate; scalar_t__ online_prev; scalar_t__ online_next; int /*<<< orphan*/  last_visited; } ;
typedef  TYPE_2__ user_t ;
struct lev_delete_user {int user_id; } ;
struct TYPE_19__ {TYPE_1__* right; TYPE_1__* left; } ;

/* Variables and functions */
 int /*<<< orphan*/  AdSpace ; 
 TYPE_2__** User ; 
 int /*<<< orphan*/  active_ad_nodes ; 
 int /*<<< orphan*/  clicked_ad_nodes ; 
 int conv_user_id (int) ; 
 int /*<<< orphan*/  delete_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exact_strfree (scalar_t__) ; 
 int /*<<< orphan*/  inactive_ad_nodes ; 
 scalar_t__ intree_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  online_convert_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  online_increment (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  online_list_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_alcohol ; 
 int /*<<< orphan*/  q_bday ; 
 int /*<<< orphan*/  q_bmonth ; 
 int /*<<< orphan*/  q_browser ; 
 int /*<<< orphan*/  q_byear ; 
 int /*<<< orphan*/  q_city ; 
 int /*<<< orphan*/  q_country ; 
 int /*<<< orphan*/  q_custom1 ; 
 int /*<<< orphan*/  q_custom10 ; 
 int /*<<< orphan*/  q_custom11 ; 
 int /*<<< orphan*/  q_custom12 ; 
 int /*<<< orphan*/  q_custom13 ; 
 int /*<<< orphan*/  q_custom14 ; 
 int /*<<< orphan*/  q_custom15 ; 
 int /*<<< orphan*/  q_custom2 ; 
 int /*<<< orphan*/  q_custom3 ; 
 int /*<<< orphan*/  q_custom4 ; 
 int /*<<< orphan*/  q_custom5 ; 
 int /*<<< orphan*/  q_custom6 ; 
 int /*<<< orphan*/  q_custom7 ; 
 int /*<<< orphan*/  q_custom8 ; 
 int /*<<< orphan*/  q_custom9 ; 
 int /*<<< orphan*/  q_cvisited ; 
 int /*<<< orphan*/  q_gcountry ; 
 int /*<<< orphan*/  q_has_photo ; 
 int /*<<< orphan*/  q_height ; 
 int /*<<< orphan*/  q_hidden ; 
 int /*<<< orphan*/  q_iiothers ; 
 int /*<<< orphan*/  q_mstatus ; 
 int /*<<< orphan*/  q_operator ; 
 int /*<<< orphan*/  q_pays_money ; 
 int /*<<< orphan*/  q_political ; 
 int /*<<< orphan*/  q_ppriority ; 
 int /*<<< orphan*/  q_region ; 
 int /*<<< orphan*/  q_sex ; 
 int /*<<< orphan*/  q_smoking ; 
 int /*<<< orphan*/  q_timezone ; 
 int /*<<< orphan*/  q_uses_apps ; 
 int /*<<< orphan*/  targ_weights_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tot_users ; 
 int /*<<< orphan*/  user_clear_addresses (TYPE_2__*) ; 
 int /*<<< orphan*/  user_clear_education (TYPE_2__*) ; 
 int /*<<< orphan*/  user_clear_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  user_clear_groups (TYPE_2__*) ; 
 int /*<<< orphan*/  user_clear_interests (TYPE_2__*,int) ; 
 int /*<<< orphan*/  user_clear_langs (TYPE_2__*) ; 
 int /*<<< orphan*/  user_clear_military (TYPE_2__*) ; 
 int /*<<< orphan*/  user_clear_schools (TYPE_2__*) ; 
 int /*<<< orphan*/  user_clear_work (TYPE_2__*) ; 
 int /*<<< orphan*/  user_to_olist (TYPE_2__*) ; 
 TYPE_1__* utree_merge (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*,int) ; 

__attribute__((used)) static int delete_user (struct lev_delete_user *E) {
  int user_id = E->user_id;
  int s = conv_user_id (user_id);
  if (s < 0) {
    return 0;
  }
  user_t *U = User[s];

  if (!U) {
    return 0;
  }

  --tot_users;

  if (U->online_next) {
    online_list_remove (user_to_olist (U));
    online_increment (online_convert_time (U->last_visited), -1);
  }

  U->online_next = U->online_prev = 0;

  utree_t *new_tree = utree_merge (U->left_rate, U->right_rate);

  if (new_tree) {
    new_tree->uplink = U->uplink_rate;
  }

  if (U->uplink_rate->left == (utree_t *) U) {
    U->uplink_rate->left = new_tree;
  } else {
    U->uplink_rate->right = new_tree;
  }

  U->uplink_rate = U->left_rate = U->right_rate = 0;

  user_clear_education (U);
  user_clear_schools (U);
  user_clear_addresses (U);
  user_clear_military (U);
  user_clear_work (U);
  user_clear_groups (U);
  user_clear_langs (U);
  user_clear_field (U->uid, q_sex, U->sex);
  user_clear_field (U->uid, q_operator, U->operator);
  user_clear_field (U->uid, q_browser, U->browser);
  user_clear_field (U->uid, q_region, U->region);
  user_clear_field (U->uid, q_height, U->height);
  user_clear_field (U->uid, q_smoking, U->smoking);
  user_clear_field (U->uid, q_alcohol, U->alcohol);
  user_clear_field (U->uid, q_ppriority, U->ppriority);
  user_clear_field (U->uid, q_iiothers, U->iiothers);
  user_clear_field (U->uid, q_hidden, U->hidden);
  user_clear_field (U->uid, q_cvisited, U->cvisited);
  user_clear_field (U->uid, q_gcountry, U->gcountry);
  user_clear_field (U->uid, q_custom1, U->custom1);
  user_clear_field (U->uid, q_custom2, U->custom2);
  user_clear_field (U->uid, q_custom3, U->custom3);
  user_clear_field (U->uid, q_custom4, U->custom4);
  user_clear_field (U->uid, q_custom5, U->custom5);
  user_clear_field (U->uid, q_custom6, U->custom6);
  user_clear_field (U->uid, q_custom7, U->custom7);
  user_clear_field (U->uid, q_custom8, U->custom8);
  user_clear_field (U->uid, q_custom9, U->custom9);
  user_clear_field (U->uid, q_custom10, U->custom10);
  user_clear_field (U->uid, q_custom11, U->custom11);
  user_clear_field (U->uid, q_custom12, U->custom12);
  user_clear_field (U->uid, q_custom13, U->custom13);
  user_clear_field (U->uid, q_custom14, U->custom14);
  user_clear_field (U->uid, q_custom15, U->custom15);
  user_clear_field (U->uid, q_timezone, U->timezone);
  user_clear_field (U->uid, q_has_photo, (U->has_photo & 0x81) == 1);
  user_clear_field (U->uid, q_uses_apps, (U->has_photo & 0x82) == 2);
  user_clear_field (U->uid, q_pays_money, (U->has_photo & 0x84) == 4);
  user_clear_field (U->uid, q_mstatus, U->mstatus);
  user_clear_field (U->uid, q_political, U->political);
  user_clear_field (U->uid, q_country, U->uni_country);
  user_clear_field (U->uid, q_city, U->uni_city);
  delete_user_hashlist (U->uid, U->name_hashes);
  delete_user_hashlist (U->uid, U->religion_hashes);
  delete_user_hashlist (U->uid, U->hometown_hashes);
  delete_user_hashlist (U->uid, U->proposal_hashes);
  user_clear_field (U->uid, q_byear, U->bday_year);
  user_clear_field (U->uid, q_bmonth, U->bday_month);
  user_clear_field (U->uid, q_bday, U->bday_day);
  exact_strfree (U->religion);
  exact_strfree (U->name);
  exact_strfree (U->hometown);
  exact_strfree (U->proposal);
  U->name = 0;
  user_clear_interests (U, -1);

  active_ad_nodes -= intree_free (AdSpace, U->active_ads);
  inactive_ad_nodes -= intree_free (AdSpace, U->inactive_ads);
  clicked_ad_nodes -= intree_free (AdSpace, U->clicked_ads);
  if (U->weights) {
    targ_weights_vector_free (U->weights);
    U->weights = NULL;
  }
  zfree (U, sizeof (user_t));
  User[s] = 0;

  return 1;
}