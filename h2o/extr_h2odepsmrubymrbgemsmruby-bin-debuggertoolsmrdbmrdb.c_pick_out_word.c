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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 scalar_t__ ISBLANK (char) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static char*
pick_out_word(mrb_state *mrb, char **pp)
{
  char *ps;

  for (ps=*pp; ISBLANK(*ps); ps++) ;
  if (*ps == '\0') {
    return NULL;
  }

  if (*ps == '\"' || *ps == '\'') {
    *pp = strchr(ps+1, *ps);
    if (*pp) (*pp)++;
  }
  else {
    *pp = strpbrk(ps, " \t");
  }

  if (!*pp) {
    *pp = ps + strlen(ps);
  }

  if (**pp != '\0') {
    **pp = '\0';
    (*pp)++;
  }

  return ps;
}