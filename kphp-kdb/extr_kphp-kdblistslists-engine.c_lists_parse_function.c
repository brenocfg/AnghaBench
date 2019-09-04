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
 int /*<<< orphan*/  TL_ERROR_UNKNOWN_FUNCTION_ID ; 
 int /*<<< orphan*/  TL_ERROR_WRONG_ACTOR_ID ; 
#define  TL_LISTS_ADD_ENTRY 181 
#define  TL_LISTS_CHANGE_FLAGS 180 
#define  TL_LISTS_CHANGE_LIST_FLAGS 179 
#define  TL_LISTS_CHANGE_LIST_FLAGS_EX 178 
#define  TL_LISTS_DATEDISTR 177 
#define  TL_LISTS_DECR_FLAGS 176 
#define  TL_LISTS_DECR_VALUE 175 
#define  TL_LISTS_DECR_VALUE_OR_CREATE 174 
#define  TL_LISTS_DELETE_ENTRY 173 
#define  TL_LISTS_DELETE_LIST 172 
#define  TL_LISTS_DELETE_OBJECT 171 
#define  TL_LISTS_DELETE_SUBLIST 170 
#define  TL_LISTS_DELETE_SUBLIST_EX 169 
#define  TL_LISTS_GET_ENTRY 168 
#define  TL_LISTS_GET_ENTRY_DATE 167 
#define  TL_LISTS_GET_ENTRY_FLAGS 166 
#define  TL_LISTS_GET_ENTRY_GLOBAL_ID 165 
#define  TL_LISTS_GET_ENTRY_POS 164 
#define  TL_LISTS_GET_ENTRY_TEXT 163 
#define  TL_LISTS_GET_ENTRY_VALUE 162 
#define  TL_LISTS_GET_LIST 161 
#define  TL_LISTS_GET_LIST_COUNT 160 
#define  TL_LISTS_GET_LIST_FULL 159 
#define  TL_LISTS_GET_LIST_FULL_LIMIT 158 
#define  TL_LISTS_GET_LIST_LIMIT 157 
#define  TL_LISTS_GET_SUBLISTS_COUNT 156 
#define  TL_LISTS_GET_SUBLIST_COUNT 155 
#define  TL_LISTS_INCR_FLAGS 154 
#define  TL_LISTS_INCR_VALUE 153 
#define  TL_LISTS_INCR_VALUE_OR_CREATE 152 
#define  TL_LISTS_INTERSECT 151 
#define  TL_LISTS_INTERSECT_FULL 150 
#define  TL_LISTS_INTERSECT_FULL_LIMIT 149 
#define  TL_LISTS_INTERSECT_LIMIT 148 
#define  TL_LISTS_INTERSECT_WILD 147 
#define  TL_LISTS_INTERSECT_WILD_FULL 146 
#define  TL_LISTS_INTERSECT_WILD_FULL_LIMIT 145 
#define  TL_LISTS_INTERSECT_WILD_LIMIT 144 
#define  TL_LISTS_REPLACE_ENTRY 143 
#define  TL_LISTS_SET_ENTRY 142 
#define  TL_LISTS_SET_ENTRY_TEXT 141 
#define  TL_LISTS_SET_FLAGS 140 
#define  TL_LISTS_SET_LIST_FLAGS 139 
#define  TL_LISTS_SET_VALUE 138 
#define  TL_LISTS_SORTED_LIST 137 
#define  TL_LISTS_SORTED_LIST_FULL 136 
#define  TL_LISTS_SORTED_LIST_FULL_LIMIT 135 
#define  TL_LISTS_SORTED_LIST_LIMIT 134 
#define  TL_LISTS_SUBTRACT 133 
#define  TL_LISTS_SUBTRACT_LIMIT 132 
#define  TL_LISTS_SUMLIST 131 
#define  TL_LISTS_SUMLIST_WEIGHTED 130 
#define  TL_LISTS_SUMLIST_WEIGHTED_WILD 129 
#define  TL_LISTS_SUMLIST_WILD 128 
 struct tl_act_extra* tl_datedistr () ; 
 int /*<<< orphan*/  tl_do_list_entry_get ; 
 scalar_t__ tl_fetch_error () ; 
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_set_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int) ; 
 struct tl_act_extra* tl_list_count (int) ; 
 struct tl_act_extra* tl_list_delete () ; 
 struct tl_act_extra* tl_list_entry_delete () ; 
 struct tl_act_extra* tl_list_entry_get (int /*<<< orphan*/ ) ; 
 struct tl_act_extra* tl_list_entry_get_int (int,int) ; 
 struct tl_act_extra* tl_list_entry_get_pos () ; 
 struct tl_act_extra* tl_list_entry_get_text () ; 
 struct tl_act_extra* tl_list_entry_incr_or_create (int) ; 
 struct tl_act_extra* tl_list_entry_set (int) ; 
 struct tl_act_extra* tl_list_entry_set_flags (int) ; 
 struct tl_act_extra* tl_list_entry_set_text () ; 
 struct tl_act_extra* tl_list_entry_set_value (int) ; 
 struct tl_act_extra* tl_list_get (int,int) ; 
 struct tl_act_extra* tl_list_intersect (int,int,int,int) ; 
 struct tl_act_extra* tl_list_set_flags (int) ; 
 struct tl_act_extra* tl_list_sorted (int,int) ; 
 struct tl_act_extra* tl_list_sum (int,int) ; 
 struct tl_act_extra* tl_object_delete () ; 
 struct tl_act_extra* tl_sublist_delete (int) ; 

struct tl_act_extra *lists_parse_function (long long actor_id) {
  if (actor_id != 0) {
    tl_fetch_set_error ("Lists only support actor_id = 0", TL_ERROR_WRONG_ACTOR_ID);
    return 0;
  }
  int op = tl_fetch_int ();
  if (tl_fetch_error ()) {
    return 0;
  }
  switch (op) {
  case TL_LISTS_DELETE_LIST:
    return tl_list_delete ();
  case TL_LISTS_DELETE_ENTRY:
    return tl_list_entry_delete ();
  case TL_LISTS_DELETE_OBJECT:
    return tl_object_delete ();
  case TL_LISTS_SET_ENTRY:
    return tl_list_entry_set (0);
  case TL_LISTS_ADD_ENTRY:
    return tl_list_entry_set (2);
  case TL_LISTS_REPLACE_ENTRY:
    return tl_list_entry_set (1);
  case TL_LISTS_SET_ENTRY_TEXT:
    return tl_list_entry_set_text ();
  case TL_LISTS_SET_FLAGS:
    return tl_list_entry_set_flags (0);
  case TL_LISTS_CHANGE_FLAGS:
    return tl_list_entry_set_flags (1);
  case TL_LISTS_INCR_FLAGS:
    return tl_list_entry_set_flags (2);
  case TL_LISTS_DECR_FLAGS:
    return tl_list_entry_set_flags (3);
  case TL_LISTS_SET_VALUE:
    return tl_list_entry_set_value (0);
  case TL_LISTS_INCR_VALUE:
    return tl_list_entry_set_value (1);
  case TL_LISTS_DECR_VALUE:
    return tl_list_entry_set_value (2);
  case TL_LISTS_INCR_VALUE_OR_CREATE:
    return tl_list_entry_incr_or_create (0);
  case TL_LISTS_DECR_VALUE_OR_CREATE:
    return tl_list_entry_incr_or_create (1);
  case TL_LISTS_SET_LIST_FLAGS:
    return tl_list_set_flags (0);
  case TL_LISTS_CHANGE_LIST_FLAGS:
    return tl_list_set_flags (1);
  case TL_LISTS_CHANGE_LIST_FLAGS_EX:
    return tl_list_set_flags (2);
  case TL_LISTS_DELETE_SUBLIST:
    return tl_sublist_delete (0);
  case TL_LISTS_DELETE_SUBLIST_EX:
    return tl_sublist_delete (1);
  case TL_LISTS_GET_ENTRY:
    return tl_list_entry_get (tl_do_list_entry_get);
  case TL_LISTS_GET_ENTRY_FLAGS:
    return tl_list_entry_get_int (0, 0);
  case TL_LISTS_GET_ENTRY_DATE:
    return tl_list_entry_get_int (0, 1);
  case TL_LISTS_GET_ENTRY_GLOBAL_ID:
    return tl_list_entry_get_int (1, 2);
  case TL_LISTS_GET_ENTRY_VALUE:
    return tl_list_entry_get_int (1, 4);
  case TL_LISTS_GET_ENTRY_TEXT:
    return tl_list_entry_get_text ();
  case TL_LISTS_GET_ENTRY_POS:
    return tl_list_entry_get_pos ();
  case TL_LISTS_GET_LIST:
    return tl_list_get (0, 0);
  case TL_LISTS_GET_LIST_LIMIT:
    return tl_list_get (0, 1);
  case TL_LISTS_GET_LIST_FULL:
    return tl_list_get (1, 0);
  case TL_LISTS_GET_LIST_FULL_LIMIT:
    return tl_list_get (1, 1);
  case TL_LISTS_GET_LIST_COUNT:
    return tl_list_count (0);
  case TL_LISTS_GET_SUBLIST_COUNT:
    return tl_list_count (1);
  case TL_LISTS_GET_SUBLISTS_COUNT:
    return tl_list_count (2);
  case TL_LISTS_INTERSECT:
    return tl_list_intersect (1, 0, 0, 0);
  case TL_LISTS_INTERSECT_LIMIT:
    return tl_list_intersect (1, 0, 1, 0);
  case TL_LISTS_INTERSECT_FULL:
    return tl_list_intersect (1, 0, 0, 1);
  case TL_LISTS_INTERSECT_FULL_LIMIT:
    return tl_list_intersect (1, 0, 1, 1);
  case TL_LISTS_INTERSECT_WILD:
    return tl_list_intersect (1, 1, 0, 0);
  case TL_LISTS_INTERSECT_WILD_LIMIT:
    return tl_list_intersect (1, 1, 1, 0);
  case TL_LISTS_INTERSECT_WILD_FULL:
    return tl_list_intersect (1, 1, 0, 1);
  case TL_LISTS_INTERSECT_WILD_FULL_LIMIT:
    return tl_list_intersect (1, 1, 1, 1);
  case TL_LISTS_SUBTRACT:
    return tl_list_intersect (0, 0, 0, 0);
  case TL_LISTS_SUBTRACT_LIMIT:
    return tl_list_intersect (0, 0, 1, 0);
  case TL_LISTS_SUMLIST:
    return tl_list_sum (0, 0);
  case TL_LISTS_SUMLIST_WILD:
    return tl_list_sum (1, 0);
  case TL_LISTS_SUMLIST_WEIGHTED:
    return tl_list_sum (0, 1);
  case TL_LISTS_SUMLIST_WEIGHTED_WILD:
    return tl_list_sum (1, 1);
  case TL_LISTS_SORTED_LIST:
    return tl_list_sorted (0, 0);
  case TL_LISTS_SORTED_LIST_LIMIT:
    return tl_list_sorted (0, 1);
  case TL_LISTS_SORTED_LIST_FULL:
    return tl_list_sorted (1, 0);
  case TL_LISTS_SORTED_LIST_FULL_LIMIT:
    return tl_list_sorted (1, 1);
  case TL_LISTS_DATEDISTR:
    return tl_datedistr ();
  default:
    tl_fetch_set_error_format (TL_ERROR_UNKNOWN_FUNCTION_ID, "Unknown op %08x", op);
    return 0;
  }
}