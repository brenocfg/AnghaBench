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
struct tl_act_extra {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_MODE ; 
 int /*<<< orphan*/  NOTIFY_MODE ; 
 int /*<<< orphan*/  RECOMMEND_MODE ; 
#define  TL_CNEWS_ADD_BOOKMARK 152 
#define  TL_CNEWS_DELETE_UPDATE 151 
#define  TL_CNEWS_DELETE_UPDATES 150 
#define  TL_CNEWS_DEL_BOOKMARK 149 
#define  TL_CNEWS_GET_RAW_UPDATES 148 
#define  TL_CNEWS_GET_RAW_USER_UPDATES 147 
#define  TL_CNEWS_UNDELETE_UPDATE 146 
#define  TL_CNEWS_UPDATE 145 
 int /*<<< orphan*/  TL_ERROR_UNKNOWN_FUNCTION_ID ; 
 int /*<<< orphan*/  TL_ERROR_WRONG_ACTOR_ID ; 
#define  TL_NEWS_DELETE_UPDATES 144 
#define  TL_NEWS_GET_PRIVACY_MASK 143 
#define  TL_NEWS_GET_RAW_UPDATES 142 
#define  TL_NEWS_SET_PRIVACY_MASK 141 
#define  TL_NEWS_UPDATE 140 
#define  TL_NNEWS_DELETE_UPDATE 139 
#define  TL_NNEWS_DELETE_UPDATES 138 
#define  TL_NNEWS_DELETE_USER_UPDATE 137 
#define  TL_NNEWS_GET_GROUPED_UPDATES 136 
#define  TL_NNEWS_GET_UPDATES 135 
#define  TL_NNEWS_UNDELETE_UPDATE 134 
#define  TL_NNEWS_UNDELETE_USER_UPDATE 133 
#define  TL_NNEWS_UPDATE 132 
#define  TL_RNEWS_GET_RATE 131 
#define  TL_RNEWS_GET_RAW_UPDATES 130 
#define  TL_RNEWS_SET_RATE 129 
#define  TL_RNEWS_UPDATE 128 
 int /*<<< orphan*/  UG_MODE ; 
 struct tl_act_extra* tl_cnews_add_bookmark () ; 
 struct tl_act_extra* tl_cnews_del_bookmark () ; 
 struct tl_act_extra* tl_cnews_delete_update () ; 
 struct tl_act_extra* tl_cnews_delete_updates () ; 
 struct tl_act_extra* tl_cnews_get_raw_updates () ; 
 struct tl_act_extra* tl_cnews_get_raw_user_updates () ; 
 struct tl_act_extra* tl_cnews_undelete_update () ; 
 struct tl_act_extra* tl_cnews_update () ; 
 scalar_t__ tl_fetch_error () ; 
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_set_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int) ; 
 struct tl_act_extra* tl_news_delete () ; 
 struct tl_act_extra* tl_news_error_bad_mode (int) ; 
 struct tl_act_extra* tl_news_get_privacy_mask () ; 
 struct tl_act_extra* tl_news_get_raw_updates () ; 
 struct tl_act_extra* tl_news_set_privacy_mask () ; 
 struct tl_act_extra* tl_news_update () ; 
 struct tl_act_extra* tl_nnews_delete_update () ; 
 struct tl_act_extra* tl_nnews_delete_updates () ; 
 struct tl_act_extra* tl_nnews_delete_user_update () ; 
 struct tl_act_extra* tl_nnews_get_grouped_updates () ; 
 struct tl_act_extra* tl_nnews_get_updates () ; 
 struct tl_act_extra* tl_nnews_undelete_update () ; 
 struct tl_act_extra* tl_nnews_undelete_user_update () ; 
 struct tl_act_extra* tl_nnews_update () ; 
 struct tl_act_extra* tl_rnews_get_rate () ; 
 struct tl_act_extra* tl_rnews_get_raw_updates () ; 
 struct tl_act_extra* tl_rnews_set_rate () ; 
 struct tl_act_extra* tl_rnews_update () ; 

struct tl_act_extra *news_parse_function (long long actor_id) {
  if (actor_id != 0) {
    tl_fetch_set_error ("News only support actor_id = 0", TL_ERROR_WRONG_ACTOR_ID);
    return 0;
  }
  int op = tl_fetch_int ();
  if (tl_fetch_error ()) {
    return 0;
  }
  switch (op) {
  case TL_NEWS_UPDATE:
    if (!UG_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_news_update ();
  case TL_NEWS_DELETE_UPDATES:
    if (!UG_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_news_delete ();
  case TL_NEWS_SET_PRIVACY_MASK:
    if (!UG_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_news_set_privacy_mask ();
  case TL_NEWS_GET_PRIVACY_MASK:
    if (!UG_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_news_get_privacy_mask ();
  case TL_NEWS_GET_RAW_UPDATES:
    if (!UG_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_news_get_raw_updates ();
  case TL_NNEWS_UPDATE:
    if (!NOTIFY_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_nnews_update ();
  case TL_NNEWS_DELETE_UPDATES:
    if (!NOTIFY_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_nnews_delete_updates ();
  case TL_NNEWS_DELETE_UPDATE:
    if (!NOTIFY_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_nnews_delete_update ();
  case TL_NNEWS_UNDELETE_UPDATE:
    if (!NOTIFY_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_nnews_undelete_update ();
  case TL_NNEWS_DELETE_USER_UPDATE:
    if (!NOTIFY_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_nnews_delete_user_update ();
  case TL_NNEWS_UNDELETE_USER_UPDATE:
    if (!NOTIFY_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_nnews_undelete_user_update ();
  case TL_NNEWS_GET_UPDATES:
    if (!NOTIFY_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_nnews_get_updates ();
  case TL_NNEWS_GET_GROUPED_UPDATES:
    if (!NOTIFY_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_nnews_get_grouped_updates ();
  case TL_CNEWS_UPDATE:
    if (!COMM_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_cnews_update ();
  case TL_CNEWS_DELETE_UPDATES:
    if (!COMM_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_cnews_delete_updates ();
  case TL_CNEWS_DELETE_UPDATE:
    if (!COMM_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_cnews_delete_update ();
  case TL_CNEWS_UNDELETE_UPDATE:
    if (!COMM_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_cnews_undelete_update ();
  case TL_CNEWS_GET_RAW_UPDATES:
    if (!COMM_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_cnews_get_raw_updates ();
  case TL_CNEWS_GET_RAW_USER_UPDATES:
    if (!COMM_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_cnews_get_raw_user_updates ();
  case TL_CNEWS_ADD_BOOKMARK:
    if (!COMM_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_cnews_add_bookmark ();
  case TL_CNEWS_DEL_BOOKMARK:
    if (!COMM_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_cnews_del_bookmark ();
  case TL_RNEWS_UPDATE:
    if (!RECOMMEND_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_rnews_update ();
  case TL_RNEWS_SET_RATE:
    if (!RECOMMEND_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_rnews_set_rate ();
  case TL_RNEWS_GET_RATE:
    if (!RECOMMEND_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_rnews_get_rate ();
  case TL_RNEWS_GET_RAW_UPDATES:
    if (!RECOMMEND_MODE) {
      return tl_news_error_bad_mode (op);
    }
    return tl_rnews_get_raw_updates ();
  default:
    tl_fetch_set_error_format (TL_ERROR_UNKNOWN_FUNCTION_ID, "Unknown op 0x%08x", op);
    return 0;
  }
}