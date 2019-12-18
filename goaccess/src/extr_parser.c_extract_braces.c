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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *
extract_braces (char **p)
{
  char *b1 = NULL, *b2 = NULL, *ret = NULL, *s = *p;
  int esc = 0;
  ptrdiff_t len = 0;

  /* iterate over the log format */
  for (; *s; s++) {
    if (*s == '\\') {
      esc = 1;
    } else if (*s == '{' && !esc) {
      b1 = s;
    } else if (*s == '}' && !esc) {
      b2 = s;
      break;
    } else {
      esc = 0;
    }
  }

  if ((!b1) || (!b2))
    return NULL;
  if ((len = b2 - (b1 + 1)) <= 0)
    return NULL;

  /* Found braces, extract 'reject' character set. */
  ret = xmalloc (len + 1);
  memcpy (ret, b1 + 1, len);
  ret[len] = '\0';
  (*p) = b2 + 1;

  return ret;
}