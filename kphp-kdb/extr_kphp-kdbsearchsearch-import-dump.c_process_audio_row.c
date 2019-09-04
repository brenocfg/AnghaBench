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
struct lev_search_text_short_entry {int rate; int rate2; unsigned int obj_id; char* text; scalar_t__ type; } ;
struct lev_search_text_long_entry {int rate; int rate2; unsigned int obj_id; int text_len; char* text; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int* I ; 
 int* L ; 
 int /*<<< orphan*/  LEV_SEARCH_TEXT_LONG ; 
 scalar_t__ LEV_SEARCH_TEXT_SHORT ; 
 char** S ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t au_duration ; 
 size_t au_has_lyrics ; 
 size_t au_id ; 
 size_t au_owner_id ; 
 size_t au_performer ; 
 size_t au_source ; 
 size_t au_title ; 
 int /*<<< orphan*/  fits (int) ; 
 void* write_alloc (int) ; 

void process_audio_row (void) {
  char *p, *q;
  int len, i, c;
  struct lev_search_text_short_entry *LS;
  struct lev_search_text_long_entry *LL;

  if (I[au_source] || !fits(I[au_owner_id])) {
    return;
  }

  len = L[au_performer] + L[au_title] + 1;
  if (len > 4095) {
    return;
  }

  if (len < 256) {
    LS = write_alloc (21+len);
    LS->type = LEV_SEARCH_TEXT_SHORT + len;
    LS->rate = (I[au_has_lyrics] > 0);
    LS->rate2 = I[au_duration];
    LS->obj_id = (I[au_id] << 32) + (unsigned) I[au_owner_id];
    q = LS->text;
  } else {
    LL = write_alloc (23+len);
    LL->type = LEV_SEARCH_TEXT_LONG;
    LL->rate = (I[au_has_lyrics] > 0);
    LL->rate2 = I[au_duration];
    LL->obj_id = (I[au_id] << 32) + (unsigned) I[au_owner_id];
    LL->text_len = len;
    q = LL->text;
  }

  p = S[au_performer];
  for (i = L[au_performer]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = '\t';

  p = S[au_title];
  for (i = L[au_title]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = 0;

  adj_rec++;

}