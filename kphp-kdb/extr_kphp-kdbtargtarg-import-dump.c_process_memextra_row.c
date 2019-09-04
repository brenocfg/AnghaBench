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
struct lev_interests {int user_id; int /*<<< orphan*/  text; scalar_t__ len; scalar_t__ type; } ;

/* Variables and functions */
 int* I ; 
 scalar_t__* L ; 
 scalar_t__ LEV_TARG_INTERESTS ; 
 char** S ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/ * allowed ; 
 int /*<<< orphan*/  fits (int) ; 
 int /*<<< orphan*/  keep_word (char*,int) ; 
 size_t me_id ; 
 size_t me_text ; 
 int output_format ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strtol (char*,char**,int) ; 
 int user_id ; 
 struct lev_interests* write_alloc (scalar_t__) ; 

void process_memextra_row (void) {
  int uid = I[me_id] / 1000;
  int type = (I[me_id] % 1000) / 10;
  char *p, *q, *r;
  int c;
  user_id = uid;

  if (!fits(uid)) {
    return;
  }
  if (type <= 0 || type > 7) {
    return;
  }
//  fprintf (stderr, "orig: '%s'\n", S[me_text]);

  if (output_format != 1) {
    struct lev_interests *D = write_alloc (11+L[me_text]);
    D->type = LEV_TARG_INTERESTS + type;
    D->user_id = user_id;
    D->len = L[me_text];
    strcpy (D->text, S[me_text]);

    adj_rec++;
    return;
  }

  p = q = S[me_text];
  while (*p) {
    c = (unsigned char) *p;
    if (c == '&') {
      if (p[1] == '#') {
        c = strtol(p+2, &r, 10);
        if (!*r) { break; }
        if (r > p+2 && *r == ';') {
          if (c < 128 || c == 10006 || c == 8236) {
            p = r + 1;
            *q++ = ' ';
            continue;
          }
          while (p <= r) { 
            *q++ = *p++;
          }
          continue;
        }
        p += 2;
        continue;
      }
      if (p[1] >= 'a' && p[1] <= 'z') {
        r = p + 1;
        while (*r >= 'a' && *r <= 'z') { r++; }
        if (!*r) {
          break;
        }
        if (*r == ';') {
          p = r + 1;
          *q++ = ' ';
          continue;
        }
      }
      *q++ = ' ';
      p++;
      continue;
    }
    if (c == '<') {
      if (p[1] == 'b' && p[2] == 'r' && p[3] == '>') {
        *q++ = ' ';
        p += 4;
        continue;
      }
      if (p[1] == '/' && p[2] == 'b' && p[3] == 'r' && p[4] == '>') {
        *q++ = ' ';
        p += 5;
        continue;
      }
    }
    if (c < 128 && !allowed[c]) { c = ' '; }
    if (c == 0xa8) { c = 0xc5; }
    if (c == 0xb8) { c = 0xe5; }
//    if (c == '>' || c < ' ') { c = ' '; }
    *q++ = c;
    p++;
  }
  q[0] = 0;

  c = 0;
  for (p = q = S[me_text]; *p; p++) {
    if (*p != c) { 
      *q++ = c = *p;
      if (c != ' ') { c = 0; }
    }
  }

  q[0] = q[1] = 0;
        
  p = S[me_text];

//  fprintf (stderr, "text: '%s'\n", p);

  do {
    while ((unsigned char) *p <= ' ' && *p) { p++; }
    if (!*p) { break; }
    if (*p == ',') { p++; continue; }
    q = p;
    while (*p && *p != ',') { p++; }
    while (p > q && p[-1] == ' ') { p--; }
    *p = 0;
    if (output_format == 1) {
      keep_word (q, p-q);
    }
  } while (1);

  adj_rec++;

}