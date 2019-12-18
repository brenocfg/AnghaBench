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
struct lev_search_text_short_entry {int rate2; unsigned int obj_id; char* text; scalar_t__ rate; scalar_t__ type; } ;
struct lev_search_text_long_entry {int rate2; unsigned int obj_id; int text_len; char* text; scalar_t__ rate; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int* I ; 
 int* L ; 
 int /*<<< orphan*/  LEV_SEARCH_TEXT_LONG ; 
 scalar_t__ LEV_SEARCH_TEXT_SHORT ; 
 char** S ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  fits (int) ; 
 size_t vi_description ; 
 size_t vi_duration ; 
 size_t vi_id ; 
 size_t vi_owner_id ; 
 size_t vi_privacy ; 
 size_t vi_source ; 
 size_t vi_title ; 
 size_t vi_uploaded ; 
 void* write_alloc (int) ; 

void process_video_row (void) {
  char *p, *q;
  int len, i, c;
  struct lev_search_text_short_entry *LS;
  struct lev_search_text_long_entry *LL;

  if (I[vi_source] || I[vi_uploaded] != 1 || I[vi_privacy] || !fits(I[vi_owner_id])) {
    return;
  }

  len = L[vi_title] + L[vi_description] + 1;
  if (len > 4095) {
    return;
  }

  if (len < 256) {
    LS = write_alloc (21+len);
    LS->type = LEV_SEARCH_TEXT_SHORT + len;
    LS->rate = 0;
    LS->rate2 = I[vi_duration];
    LS->obj_id = (I[vi_id] << 32) + (unsigned) I[vi_owner_id];
    q = LS->text;
  } else {
    LL = write_alloc (23+len);
    LL->type = LEV_SEARCH_TEXT_LONG;
    LL->rate = 0;
    LL->rate2 = I[vi_duration];
    LL->obj_id = (I[vi_id] << 32) + (unsigned) I[vi_owner_id];
    LL->text_len = len;
    q = LL->text;
  }

  p = S[vi_title];
  for (i = L[vi_title]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = '\t';

  p = S[vi_description];
  for (i = L[vi_description]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = 0;

  adj_rec++;

}