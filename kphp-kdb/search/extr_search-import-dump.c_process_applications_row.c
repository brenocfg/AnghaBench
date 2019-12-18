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
 size_t ap_description ; 
 size_t ap_enabled ; 
 size_t ap_id ; 
 size_t ap_language_id ; 
 size_t ap_name ; 
 size_t ap_rate ; 
 size_t ap_server ; 
 size_t ap_size ; 
 size_t ap_type ; 
 int /*<<< orphan*/  fits (int) ; 
 int make_tag (char*,char,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 void* write_alloc (int) ; 

void process_applications_row (void) {
  char *p, *q;
  int len, i, c, tag_len;
  static char tag[64];
  struct lev_search_text_short_entry *LS;
  struct lev_search_text_long_entry *LL;

  if (!I[ap_server] || !fits(I[ap_id])) {
    return;
  }

  i = I[ap_type];
  if (i > 0) {
    tag_len = make_tag (tag, 'T', i);
  } else {
    tag_len = 0;
  }

  i = I[ap_enabled];
  if (i == 2 || i == -2 || i == 3 || i == -3) {
    tag_len += make_tag (tag + tag_len, 'B', 1);
  }

  if (I[ap_language_id] >= 0) {
    tag_len += make_tag (tag + tag_len, 'L', I[ap_language_id]);
  }

  tag_len += make_tag (tag + tag_len, 'A', 0) + 1;

  len = tag_len + L[ap_name] + L[ap_description] + 1;

  if (len > 4095) {
    return;
  }

  if (len < 256) {
    LS = write_alloc (21+len);
    LS->type = LEV_SEARCH_TEXT_SHORT + len;
    LS->rate = I[ap_rate];
    LS->rate2 = I[ap_size];
    LS->obj_id = I[ap_id];
    q = LS->text;
  } else {
    LL = write_alloc (23+len);
    LL->type = LEV_SEARCH_TEXT_LONG;
    LL->rate = I[ap_rate];
    LL->rate2 = I[ap_size];
    LL->obj_id = I[ap_id];
    LL->text_len = len;
    q = LL->text;
  }

  if (tag_len) {
    memcpy (q, tag, tag_len);
    q += tag_len;
    q[-1] = ' ';
  }

  p = S[ap_name];
  for (i = L[ap_name]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = '\t';

  p = S[ap_description];
  for (i = L[ap_description]; i > 0; i--) {
    c = (unsigned char) *p++;
    if (c < ' ') { c = ' '; }
    *q++ = c;
  }

  *q++ = 0;

  adj_rec++;
}