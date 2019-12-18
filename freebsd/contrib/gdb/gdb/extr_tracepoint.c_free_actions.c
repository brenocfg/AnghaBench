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
struct tracepoint {struct action_line* actions; } ;
struct action_line {struct action_line* action; struct action_line* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct action_line*) ; 

void
free_actions (struct tracepoint *t)
{
  struct action_line *line, *next;

  for (line = t->actions; line; line = next)
    {
      next = line->next;
      if (line->action)
	xfree (line->action);
      xfree (line);
    }
  t->actions = NULL;
}