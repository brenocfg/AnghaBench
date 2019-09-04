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

/* Variables and functions */
 scalar_t__ Q_userlist ; 
#define  TL_TARG_AD_CLICKS 158 
#define  TL_TARG_AD_CTR 157 
#define  TL_TARG_AD_CTR_SUMP 156 
#define  TL_TARG_AD_DISABLE 155 
#define  TL_TARG_AD_ENABLE 154 
#define  TL_TARG_AD_ENABLE_PRICE 153 
#define  TL_TARG_AD_INFO 152 
#define  TL_TARG_AD_LIMITED_VIEWS 151 
#define  TL_TARG_AD_MONEY 150 
#define  TL_TARG_AD_PRICING 149 
#define  TL_TARG_AD_RECENT_VIEWS 148 
#define  TL_TARG_AD_SET_AUD 147 
#define  TL_TARG_AD_SET_CATEGORIES 146 
#define  TL_TARG_AD_SET_CTR 145 
#define  TL_TARG_AD_SET_CTR_SUMP 144 
#define  TL_TARG_AD_SET_DOMAIN 143 
#define  TL_TARG_AD_SET_FACTOR 142 
#define  TL_TARG_AD_SET_GROUP 141 
#define  TL_TARG_AD_SET_SUMP 140 
#define  TL_TARG_AD_SITES 139 
#define  TL_TARG_AD_SUMP 138 
#define  TL_TARG_AD_VIEWS 137 
#define  TL_TARG_AD_VIEWS_RATE_LIMIT 136 
#define  TL_TARG_AUDIENCE 135 
#define  TL_TARG_DELETE_GROUP 134 
#define  TL_TARG_PRICES 133 
#define  TL_TARG_RECENT_AD_VIEWERS 132 
#define  TL_TARG_RECENT_VIEWS_STATS 131 
#define  TL_TARG_SEARCH 130 
#define  TL_TARG_TARGET 129 
#define  TL_TARG_TARG_AUDIENCE 128 
 int /*<<< orphan*/  assert (int) ; 
 int default_firstint_forward () ; 
 int default_random_forward () ; 
 int /*<<< orphan*/  diagonal_gather_methods ; 
 int /*<<< orphan*/  merge_forward (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sum_one_gather_methods ; 
 int /*<<< orphan*/  sum_search_gather_methods ; 
 int /*<<< orphan*/  sum_tuple_gather_methods ; 
 int /*<<< orphan*/  sum_vector_gather_methods ; 
 int tl_fetch_lookup_int () ; 

int targ_forward (void) {
  Q_userlist = 0;
  int op = tl_fetch_lookup_int ();
  assert (op);
  //struct gather_methods m;
  switch (op) {
  case TL_TARG_AD_ENABLE:
  case TL_TARG_AD_ENABLE_PRICE:
  case TL_TARG_AD_DISABLE:
  case TL_TARG_AD_SET_CTR:
  case TL_TARG_AD_SET_SUMP:
  case TL_TARG_AD_SET_CTR_SUMP:
  case TL_TARG_AD_SET_AUD:
  case TL_TARG_AD_LIMITED_VIEWS:
  case TL_TARG_AD_VIEWS_RATE_LIMIT:
  case TL_TARG_AD_SITES:
  case TL_TARG_AD_SET_FACTOR:
  case TL_TARG_AD_SET_DOMAIN:
  case TL_TARG_AD_SET_CATEGORIES:
  case TL_TARG_AD_SET_GROUP:
  case TL_TARG_DELETE_GROUP:
    merge_forward (&diagonal_gather_methods);
    return 0;
  case TL_TARG_AD_CLICKS:
  case TL_TARG_AD_MONEY:
  case TL_TARG_AD_VIEWS:
  case TL_TARG_AD_RECENT_VIEWS:
  case TL_TARG_TARGET:
    merge_forward (&sum_one_gather_methods);
    return 0;
  case TL_TARG_AD_CTR:
  case TL_TARG_AD_SUMP:
  case TL_TARG_AD_CTR_SUMP:
    merge_forward (&sum_tuple_gather_methods);
    return 0;
  case TL_TARG_RECENT_VIEWS_STATS:
  case TL_TARG_RECENT_AD_VIEWERS:
    merge_forward (&sum_vector_gather_methods);
    return 0;
  case TL_TARG_SEARCH:
    merge_forward (&sum_search_gather_methods);
    return 0;
  case TL_TARG_AD_INFO:
    return default_random_forward ();
  case TL_TARG_PRICES:
  case TL_TARG_AD_PRICING:
  case TL_TARG_TARG_AUDIENCE:
  case TL_TARG_AUDIENCE:
    //merge_forward (&sum_tuple_userlist_gather_methods);
    merge_forward (&sum_tuple_gather_methods);
    return 0;
  default:
    return default_firstint_forward ();
  }
/*    m = sum_one_gather_methods;
    m.on_send = user_list_on_send;
    merge_forward (&m);*/
}