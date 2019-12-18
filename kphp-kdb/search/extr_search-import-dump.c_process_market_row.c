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
 int /*<<< orphan*/  make_tag (char*,char,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 size_t mi_category ; 
 size_t mi_city ; 
 size_t mi_cost ; 
 size_t mi_country ; 
 size_t mi_description ; 
 size_t mi_id ; 
 size_t mi_name ; 
 size_t mi_price ; 
 size_t mi_privacy ; 
 size_t mi_section ; 
 size_t mi_votes ; 
 void* write_alloc (int) ; 

void process_market_row (void) {
  char *p, *q;
  int len, i, c, tags_len;
  static char tags[256];
  struct lev_search_text_short_entry *LS;
  struct lev_search_text_long_entry *LL;

  if (!I[mi_id] || !fits(I[mi_id]) || I[mi_privacy]) {
    return;
  }

  p = tags;

  if (I[mi_category] > 0) {
    p += make_tag (p, 'T', I[mi_category]);
  }
  if (I[mi_section] > 0) {
    p += make_tag (p, 'S', I[mi_section]);
  }
  if (I[mi_country] > 0) {
    p += make_tag (p, 'C', I[mi_country]);
  }
  if (I[mi_city] > 0) {
    p += make_tag (p, 'c', I[mi_city]);
  }

  tags_len = p - tags;
  if (tags_len > 0) {
    *p = ' ';
    tags_len++;
  }

  len = tags_len + L[mi_name] + L[mi_description] + 1;

  if (len > 8192) {
    return;
  }

  if (len < 256) {
    LS = write_alloc (21+len);
    LS->type = LEV_SEARCH_TEXT_SHORT + len;
    LS->rate = (I[mi_cost] <= I[mi_votes] ? I[mi_cost] : 0);
    LS->rate2 = (I[mi_price] > 0 ? I[mi_price] : 1000000000);
    LS->obj_id = I[mi_id];
    q = LS->text;
  } else {
    LL = write_alloc (23+len);
    LL->type = LEV_SEARCH_TEXT_LONG;
    LL->rate = (I[mi_cost] <= I[mi_votes] ? I[mi_cost] : 0);
    LL->rate2 = (I[mi_price] > 0 ? I[mi_price] : 1000000000);
    LL->obj_id = I[mi_id];
    LL->text_len = len;
    q = LL->text;
  }

  if (tags_len) {
    memcpy (q, tags, tags_len);
    q += tags_len;
  }

  p = S[mi_name];
  for (i = L[mi_name]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = '\t';

  p = S[mi_description];
  for (i = L[mi_description]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = 0;

  adj_rec++;
}