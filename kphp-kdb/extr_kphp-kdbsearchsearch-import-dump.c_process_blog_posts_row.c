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
struct lev_search_text_short_entry {unsigned int obj_id; char* text; void* rate2; void* rate; scalar_t__ type; } ;
struct lev_search_text_long_entry {unsigned int obj_id; int text_len; char* text; void* rate2; void* rate; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 void** I ; 
 int* L ; 
 int /*<<< orphan*/  LEV_SEARCH_TEXT_LONG ; 
 scalar_t__ LEV_SEARCH_TEXT_SHORT ; 
 char** S ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t bp_date ; 
 size_t bp_id ; 
 size_t bp_ncom ; 
 size_t bp_post ; 
 size_t bp_title ; 
 size_t bp_user_id ; 
 size_t bp_view_privacy ; 
 int /*<<< orphan*/  fits (void*) ; 
 void* write_alloc (int) ; 

void process_blog_posts_row (void) {
  char *p, *q;
  int len, i, c;
  struct lev_search_text_short_entry *LS;
  struct lev_search_text_long_entry *LL;

  if (!I[bp_id] || !fits(I[bp_user_id]) || I[bp_view_privacy]) {
    return;
  }

  len = L[bp_title] + L[bp_post] + 1;

  if (len > 49152) {
    return;
  }

  if (len < 256) {
    LS = write_alloc (21+len);
    LS->type = LEV_SEARCH_TEXT_SHORT + len;
    LS->rate = I[bp_date];
    LS->rate2 = I[bp_ncom];
    LS->obj_id = ((long long) I[bp_id] << 32) + (unsigned) I[bp_user_id];
    q = LS->text;
  } else {
    LL = write_alloc (23+len);
    LL->type = LEV_SEARCH_TEXT_LONG;
    LL->rate = I[bp_date];
    LL->rate2 = I[bp_ncom];
    LL->obj_id = ((long long) I[bp_id] << 32) + (unsigned) I[bp_user_id];
    LL->text_len = len;
    q = LL->text;
  }

  p = S[bp_title];
  for (i = L[bp_title]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = '\t';

  p = S[bp_post];
  for (i = L[bp_post]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = 0;

  adj_rec++;
}