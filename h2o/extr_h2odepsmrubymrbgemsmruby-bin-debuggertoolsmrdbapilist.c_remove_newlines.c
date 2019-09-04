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
typedef  int /*<<< orphan*/  mrb_bool ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_bool
remove_newlines(char *s, FILE *fp)
{
  int c;
  char *p;
  size_t len;

  if ((len = strlen(s)) == 0) {
    return FALSE;
  }

  p = s + len - 1;

  if (*p != '\r' && *p != '\n') {
    return FALSE;
  }

  if (*p == '\r') {
    /* peek the next character and skip '\n' */
    if ((c = fgetc(fp)) != '\n') {
      ungetc(c, fp);
    }
  }

  /* remove trailing newline characters */
  while (s <= p && (*p == '\r' || *p == '\n')) {
    *p-- = '\0';
  }

  return TRUE;
}