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
struct lev_search_text_short_entry {char* text; scalar_t__ obj_id; scalar_t__ rate2; scalar_t__ rate; scalar_t__ type; } ;
struct lev_search_text_long_entry {int text_len; char* text; scalar_t__ obj_id; scalar_t__ rate2; scalar_t__ rate; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__* I ; 
 int* L ; 
 int /*<<< orphan*/  LEV_SEARCH_TEXT_LONG ; 
 scalar_t__ LEV_SEARCH_TEXT_SHORT ; 
 char** S ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  fits (scalar_t__) ; 
 size_t gr_access ; 
 size_t gr_city_id ; 
 size_t gr_country_id ; 
 size_t gr_description ; 
 size_t gr_id ; 
 size_t gr_is_event ; 
 size_t gr_name ; 
 size_t gr_num ; 
 size_t gr_subtype ; 
 size_t gr_type ; 
 int /*<<< orphan*/  make_tag (char*,char,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  store_map (scalar_t__,scalar_t__) ; 
 void* write_alloc (int) ; 

void process_groups_row (void) {
  char *p, *q;
  int len, i, c, tags_len;
  static char tags[256];
  struct lev_search_text_short_entry *LS;
  struct lev_search_text_long_entry *LL;

  if (I[gr_id] > 0) {
    store_map (I[gr_id], I[gr_access]);
  }

  if (!I[gr_id] || !fits(I[gr_id]) || I[gr_is_event]) {
    return;
  }

  p = tags;

  if (I[gr_type] > 0) {
    p += make_tag (p, 'T', I[gr_type]);
  }
  if (I[gr_subtype] > 0) {
    p += make_tag (p, 'S', I[gr_subtype]);
  }
  if (I[gr_country_id] > 0) {
    p += make_tag (p, 'C', I[gr_country_id]);
  }
  if (I[gr_city_id] > 0) {
    p += make_tag (p, 'c', I[gr_city_id]);
  }

  tags_len = p - tags;
  if (tags_len > 0) {
    *p = ' ';
    tags_len++;
  }

  len = tags_len + L[gr_name] + L[gr_description] + 1;

  if (len > 8192) {
    return;
  }

  if (len < 256) {
    LS = write_alloc (21+len);
    LS->type = LEV_SEARCH_TEXT_SHORT + len;
    LS->rate = 0;
    LS->rate2 = I[gr_num];
    LS->obj_id = I[gr_id];
    q = LS->text;
  } else {
    LL = write_alloc (23+len);
    LL->type = LEV_SEARCH_TEXT_LONG;
    LL->rate = 0;
    LL->rate2 = I[gr_num];
    LL->obj_id = I[gr_id];
    LL->text_len = len;
    q = LL->text;
  }

  if (tags_len) {
    memcpy (q, tags, tags_len);
    q += tags_len;
  }

  p = S[gr_name];
  for (i = L[gr_name]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = '\t';

  p = S[gr_description];
  for (i = L[gr_description]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = 0;

  adj_rec++;
}