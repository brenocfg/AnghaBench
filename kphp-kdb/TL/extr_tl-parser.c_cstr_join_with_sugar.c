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
struct tl_token {char* text; struct tl_token* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* cstr_dup (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  tl_token_length (struct tl_token*,int*,int*) ; 
 char* tl_zzmalloc (int) ; 

char *cstr_join_with_sugar (struct tl_token *T) {
  int i, n, l;
  tl_token_length (T, &n, &l);
  assert (n >= 1);
  if (n == 1) {
    return cstr_dup (T->text);
  }
  l += n + 1;
  char *buf = tl_zzmalloc (l), *p = buf;
  for (i = 0; T != NULL; T = T->next, i++) {
    p += sprintf (p, "%s", T->text);
    *p++ = i ? ((i == n - 1) ? '>' : ',') : '<';
  }
  *p++ = 0;
  assert (p == buf + l);
  return buf;
}