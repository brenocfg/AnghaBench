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
struct lev_search_text_short_entry {unsigned int obj_id; char* text; scalar_t__ rate2; void* rate; scalar_t__ type; } ;
struct lev_search_text_long_entry {unsigned int obj_id; int text_len; char* text; scalar_t__ rate2; void* rate; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 void** I ; 
 int* L ; 
 int /*<<< orphan*/  LEV_SEARCH_TEXT_LONG ; 
 scalar_t__ LEV_SEARCH_TEXT_SHORT ; 
 char** S ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  fits (void*) ; 
 size_t mf_created ; 
 size_t mf_id ; 
 size_t mf_text ; 
 size_t mf_user_id ; 
 void* write_alloc (int) ; 

void process_minifeed_row (void) {
  char *p, *q;
  int len, i, c;
  struct lev_search_text_short_entry *LS;
  struct lev_search_text_long_entry *LL;

  if (!I[mf_id] || !fits(I[mf_user_id])) {
    return;
  }

  len = L[mf_text];

  if (len > 8192) {
    return;
  }

  if (len < 256) {
    LS = write_alloc (21+len);
    LS->type = LEV_SEARCH_TEXT_SHORT + len;
    LS->rate = I[mf_created];
    LS->rate2 = 0;
    LS->obj_id = ((long long) I[mf_id] << 32) + (unsigned) I[mf_user_id];
    q = LS->text;
  } else {
    LL = write_alloc (23+len);
    LL->type = LEV_SEARCH_TEXT_LONG;
    LL->rate = I[mf_created];
    LL->rate2 = 0;
    LL->obj_id = ((long long) I[mf_id] << 32) + (unsigned) I[mf_user_id];
    LL->text_len = len;
    q = LL->text;
  }

  p = S[mf_text];
  for (i = L[mf_text]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = 0;

  adj_rec++;
}