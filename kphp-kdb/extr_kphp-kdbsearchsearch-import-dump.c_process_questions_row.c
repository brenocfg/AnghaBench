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
struct lev_search_text_short_entry {unsigned int obj_id; char* text; scalar_t__ rate2; scalar_t__ rate; scalar_t__ type; } ;
struct lev_search_text_long_entry {unsigned int obj_id; int text_len; char* text; scalar_t__ rate2; scalar_t__ rate; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__* I ; 
 int* L ; 
 int /*<<< orphan*/  LEV_SEARCH_TEXT_LONG ; 
 scalar_t__ LEV_SEARCH_TEXT_SHORT ; 
 char** S ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  fits (scalar_t__) ; 
 int /*<<< orphan*/  make_tag (char*,char,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 size_t qu_date ; 
 size_t qu_id ; 
 size_t qu_message ; 
 size_t qu_num ; 
 size_t qu_owner_id ; 
 size_t qu_type ; 
 void* write_alloc (int) ; 

void process_questions_row (void) {
  char *p, *q;
  int len, i, c, tags_len;
  static char tags[256];
  struct lev_search_text_short_entry *LS;
  struct lev_search_text_long_entry *LL;

  if (!I[qu_id] || !fits(I[qu_owner_id])) {
    return;
  }

  p = tags;

  if (I[qu_type] > 0) {
    p += make_tag (p, 'T', I[qu_type]);
  }

  tags_len = p - tags;
  if (tags_len > 0) {
    *p = ' ';
    tags_len++;
  }

  len = tags_len + L[qu_message];

  if (len > 8192) {
    return;
  }

  if (len < 256) {
    LS = write_alloc (21+len);
    LS->type = LEV_SEARCH_TEXT_SHORT + len;
    LS->rate = I[qu_date];
    LS->rate2 = I[qu_num];
    LS->obj_id = ((long long) I[qu_id] << 32) + (unsigned) I[qu_owner_id];
    q = LS->text;
  } else {
    LL = write_alloc (23+len);
    LL->type = LEV_SEARCH_TEXT_LONG;
    LL->rate = I[qu_date];
    LL->rate2 = I[qu_num];
    LL->obj_id = ((long long) I[qu_id] << 32) + (unsigned) I[qu_owner_id];
    LL->text_len = len;
    q = LL->text;
  }

  if (tags_len) {
    memcpy (q, tags, tags_len);
    q += tags_len;
  }

  p = S[qu_message];
  for (i = L[qu_message]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = 0;

  adj_rec++;
}