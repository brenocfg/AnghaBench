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
struct server {int dummy; } ;
struct prompt {struct prompt* next; struct server* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  prompt_Destroy (struct prompt*,int) ; 
 struct prompt* promptlist ; 

void
log_DestroyPrompts(struct server *s)
{
  struct prompt *p, *pn, *pl;

  p = promptlist;
  pl = NULL;
  while (p) {
    pn = p->next;
    if (s && p->owner == s) {
      if (pl)
        pl->next = p->next;
      else
        promptlist = p->next;
      p->next = NULL;
      prompt_Destroy(p, 1);
    } else
      pl = p;
    p = pn;
  }
}