#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int user_id; int date; int tag; int user; int group; int owner; int place; int item; struct TYPE_3__* gnext; } ;
typedef  TYPE_1__ item_t ;

/* Variables and functions */
 int TL_NEWS_FLAG_DATE ; 
 int TL_NEWS_FLAG_GROUP ; 
 int TL_NEWS_FLAG_ITEM ; 
 int TL_NEWS_FLAG_OWNER ; 
 int TL_NEWS_FLAG_PLACE ; 
 int TL_NEWS_FLAG_TAG ; 
 int TL_NEWS_FLAG_TYPE ; 
 int TL_NEWS_FLAG_USER ; 
 int TL_NEWS_FLAG_USER_ID ; 
 int* TypeFlags ; 
 int /*<<< orphan*/  assert (int) ; 
 int* tl_store_get_ptr (int) ; 
 int /*<<< orphan*/  tl_store_int (int) ; 

__attribute__((used)) static int serialize_item_group (item_t *A, int grouping, int ug_mode) {
  item_t *B;
  int t = A->type;
  assert (t >= 0 && t < 32);
  int i;

  if (!A->gnext) {
    int flags = TL_NEWS_FLAG_TYPE | ((ug_mode <= 0) ? TL_NEWS_FLAG_USER_ID : 0) | TL_NEWS_FLAG_DATE | TL_NEWS_FLAG_TAG | TL_NEWS_FLAG_USER | TL_NEWS_FLAG_GROUP | TL_NEWS_FLAG_OWNER | TL_NEWS_FLAG_PLACE | TL_NEWS_FLAG_ITEM;
    tl_store_int (flags);
    tl_store_int (1);
    tl_store_int (1);
    tl_store_int (A->type);
    if (ug_mode <= 0) {
      tl_store_int (A->user_id);
    }
    tl_store_int (A->date);
    tl_store_int (A->tag);
    tl_store_int (A->user);
    tl_store_int (A->group);
    tl_store_int (A->owner);
    tl_store_int (A->place);
    tl_store_int (A->item);
    return 1;
  }
  int n = 0;
  for (B = A; B; B = B->gnext) {
    n ++;
  }

  int *flags = tl_store_get_ptr (4);
  tl_store_int (n);
  if (n > grouping) { n = grouping; }
  tl_store_int (n);

  *flags = TL_NEWS_FLAG_TYPE | TL_NEWS_FLAG_DATE | TL_NEWS_FLAG_TAG;
  tl_store_int (A->type);
  if (ug_mode <= 0) {
    if (TypeFlags[t] & 4) {
      *flags |= TL_NEWS_FLAG_USER_ID;
      tl_store_int (A->user_id);
    } else {
      *flags |= 2 * TL_NEWS_FLAG_USER_ID;
      for (B = A, i = 0; i < n; B = B->gnext, i ++) {
        tl_store_int (B->user_id);
      }
    }
  }

  tl_store_int (A->date);
  tl_store_int (A->tag);

  *flags |= (2 * TL_NEWS_FLAG_USER);
  for (B = A, i = 0; i < n; B = B->gnext, i ++) {
    tl_store_int (B->user);
  }

  *flags |= (2 * TL_NEWS_FLAG_GROUP);
  for (B = A, i = 0; i < n; B = B->gnext, i ++) {
    tl_store_int (B->group);
  }

  if (TypeFlags[t] & 1) {
    *flags |= TL_NEWS_FLAG_OWNER;
    tl_store_int (A->owner);
  } else {
    *flags |= (2 * TL_NEWS_FLAG_OWNER);
    for (B = A, i = 0; i < n; B = B->gnext, i ++) {
      tl_store_int (B->owner);
    }
  }

  if (TypeFlags[t] & 2) {
    *flags |= TL_NEWS_FLAG_PLACE;
    tl_store_int (A->place);
  } else {
    *flags |= (2 * TL_NEWS_FLAG_PLACE);
    for (B = A, i = 0; i < n; B = B->gnext, i ++) {
      tl_store_int (B->place);
    }
  }

  if (TypeFlags[t] & 8) {
    *flags |= TL_NEWS_FLAG_ITEM;
    tl_store_int (A->item);
  } else {
    *flags |= (2 * TL_NEWS_FLAG_ITEM);
    for (B = A, i = 0; i < n; B = B->gnext, i ++) {
      tl_store_int (B->item);
    }
  }
  return 1;
}