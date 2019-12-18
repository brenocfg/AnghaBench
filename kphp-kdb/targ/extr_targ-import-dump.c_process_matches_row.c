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
struct lev_proposal {int len; int /*<<< orphan*/  text; scalar_t__ user_id; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__* I ; 
 int* L ; 
 int /*<<< orphan*/  LEV_TARG_PROPOSAL ; 
 char** S ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  fits (scalar_t__) ; 
 size_t mp_category ; 
 size_t mp_id ; 
 size_t mp_question ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ user_id ; 
 struct lev_proposal* write_alloc (int) ; 

void process_matches_row (void) {
  struct lev_proposal *E;
  int len = L[mp_question];
  char *str = S[mp_question];
  int i;
  user_id = I[mp_id];

  if (!fits(user_id) || I[mp_category] || !len || len >= 1024) {
    return;
  }

  E = write_alloc (11 + len);
  E->type = LEV_TARG_PROPOSAL;
  E->user_id = user_id;
  E->len = len;

  for (i = 0; i < len; i++) {
    if ((unsigned char) str[i] < ' ') {
      str[i] = ' ';
    }
  }

  strcpy (E->text, str);
  adj_rec++;
}