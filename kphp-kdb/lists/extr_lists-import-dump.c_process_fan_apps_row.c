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
struct lev_set_entry_text {int object_id; int /*<<< orphan*/  text; void* list_id; scalar_t__ type; } ;

/* Variables and functions */
 void** I ; 
 int* L ; 
 scalar_t__ LEV_LI_SET_ENTRY ; 
 scalar_t__ LEV_LI_SET_ENTRY_TEXT ; 
 int /*<<< orphan*/ * S ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t af_app_id ; 
 size_t af_message ; 
 size_t af_ordering ; 
 size_t af_user_id ; 
 scalar_t__ conv_uid (void*) ; 
 void* list_id ; 
 int /*<<< orphan*/  log_2ints (scalar_t__,int,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct lev_set_entry_text* write_alloc (int) ; 

void process_fan_apps_row (void) {
  int app_id = I[af_app_id];
  list_id = I[af_user_id];
  if (conv_uid (list_id) < 0 || app_id <= 0) {
    return;
  }
  log_2ints (LEV_LI_SET_ENTRY + 19, app_id, I[af_ordering]);
  if (L[af_message] > 0 && strcmp (S[af_message], "\\N") && L[af_message] < 256) {
    struct lev_set_entry_text *E = write_alloc (12 + L[af_message]);
    E->type = LEV_LI_SET_ENTRY_TEXT + L[af_message];
    E->list_id = list_id;
    E->object_id = app_id;
    memcpy (E->text, S[af_message], L[af_message]);
  }
  adj_rec++;
}