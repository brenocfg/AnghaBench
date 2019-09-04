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
struct lev_bookmark_insert {int owner; int place; } ;

/* Variables and functions */
 scalar_t__ LEV_BOOKMARK_DELETE ; 
 scalar_t__ LEV_BOOKMARK_INSERT ; 
 struct lev_bookmark_insert* alloc_log_event (scalar_t__,int,int) ; 

void insert_bookmark_log (int user_id, int type, int owner, int place, int y) {
  struct lev_bookmark_insert *E = alloc_log_event ((y ? LEV_BOOKMARK_INSERT : LEV_BOOKMARK_DELETE) + type, sizeof (struct lev_bookmark_insert), user_id);
  E->owner = owner;
  E->place = place;
}