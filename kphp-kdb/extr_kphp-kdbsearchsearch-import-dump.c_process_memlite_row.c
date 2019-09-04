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
struct lev_search_text_short_entry {int rate; int rate2; int obj_id; char* text; scalar_t__ type; } ;
struct lev_search_text_long_entry {int rate; int rate2; int obj_id; int text_len; char* text; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int* I ; 
 int* L ; 
 int /*<<< orphan*/  LEV_SEARCH_TEXT_LONG ; 
 scalar_t__ LEV_SEARCH_TEXT_SHORT ; 
 char** S ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  fits (int) ; 
 size_t ml_cute ; 
 size_t ml_first_name ; 
 size_t ml_id ; 
 size_t ml_last_name ; 
 size_t ml_profile_privacy ; 
 size_t ml_rate ; 
 void* write_alloc (int) ; 

void process_memlite_row (void) {
  char *p, *q;
  int len, i, c;
  struct lev_search_text_short_entry *LS;
  struct lev_search_text_long_entry *LL;

  if (!I[ml_id] || !fits(I[ml_id]) || I[ml_profile_privacy] == 4) {
    return;
  }

  len = L[ml_first_name] + L[ml_last_name] + 1;

  if (len > 1024) {
    return;
  }

  if (len < 256) {
    LS = write_alloc (21+len);
    LS->type = LEV_SEARCH_TEXT_SHORT + len;
    LS->rate = I[ml_rate];
    LS->rate2 = I[ml_cute];
    LS->obj_id = I[ml_id];
    q = LS->text;
  } else {
    LL = write_alloc (23+len);
    LL->type = LEV_SEARCH_TEXT_LONG;
    LL->rate = I[ml_rate];
    LL->rate2 = I[ml_cute];
    LL->obj_id = I[ml_id];
    LL->text_len = len;
    q = LL->text;
  }

  p = S[ml_first_name];
  for (i = L[ml_first_name]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = '\t';

  p = S[ml_last_name];
  for (i = L[ml_last_name]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = 0;

  adj_rec++;
}