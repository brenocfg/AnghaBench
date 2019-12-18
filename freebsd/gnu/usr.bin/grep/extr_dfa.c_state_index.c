#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct dfa {int sindex; scalar_t__* tokens; TYPE_7__* states; int /*<<< orphan*/  salloc; } ;
struct TYPE_11__ {int nelem; TYPE_2__* elems; } ;
typedef  TYPE_3__ position_set ;
struct TYPE_14__ {int constraint; int index; } ;
struct TYPE_9__ {scalar_t__ nelem; } ;
struct TYPE_12__ {int nelem; TYPE_8__* elems; } ;
struct TYPE_13__ {int hash; int newline; int letter; int backref; int constraint; scalar_t__ first_end; TYPE_1__ mbps; TYPE_6__ elems; } ;
struct TYPE_10__ {int index; int constraint; } ;

/* Variables and functions */
 scalar_t__ BACKREF ; 
 int /*<<< orphan*/  MALLOC (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int MB_CUR_MAX ; 
 int NO_CONSTRAINT ; 
 int /*<<< orphan*/  REALLOC_IF_NECESSARY (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SUCCEEDS_IN_CONTEXT (int,int,int,int,int) ; 
 int /*<<< orphan*/  copy (TYPE_3__ const*,TYPE_6__*) ; 
 int /*<<< orphan*/  dfa_state ; 
 int /*<<< orphan*/  position ; 

__attribute__((used)) static int
state_index (struct dfa *d, position_set const *s, int newline, int letter)
{
  int hash = 0;
  int constraint;
  int i, j;

  newline = newline ? 1 : 0;
  letter = letter ? 1 : 0;

  for (i = 0; i < s->nelem; ++i)
    hash ^= s->elems[i].index + s->elems[i].constraint;

  /* Try to find a state that exactly matches the proposed one. */
  for (i = 0; i < d->sindex; ++i)
    {
      if (hash != d->states[i].hash || s->nelem != d->states[i].elems.nelem
	  || newline != d->states[i].newline || letter != d->states[i].letter)
	continue;
      for (j = 0; j < s->nelem; ++j)
	if (s->elems[j].constraint
	    != d->states[i].elems.elems[j].constraint
	    || s->elems[j].index != d->states[i].elems.elems[j].index)
	  break;
      if (j == s->nelem)
	return i;
    }

  /* We'll have to create a new state. */
  REALLOC_IF_NECESSARY(d->states, dfa_state, d->salloc, d->sindex);
  d->states[i].hash = hash;
  MALLOC(d->states[i].elems.elems, position, s->nelem);
  copy(s, &d->states[i].elems);
  d->states[i].newline = newline;
  d->states[i].letter = letter;
  d->states[i].backref = 0;
  d->states[i].constraint = 0;
  d->states[i].first_end = 0;
#ifdef MBS_SUPPORT
  if (MB_CUR_MAX > 1)
    d->states[i].mbps.nelem = 0;
#endif
  for (j = 0; j < s->nelem; ++j)
    if (d->tokens[s->elems[j].index] < 0)
      {
	constraint = s->elems[j].constraint;
	if (SUCCEEDS_IN_CONTEXT(constraint, newline, 0, letter, 0)
	    || SUCCEEDS_IN_CONTEXT(constraint, newline, 0, letter, 1)
	    || SUCCEEDS_IN_CONTEXT(constraint, newline, 1, letter, 0)
	    || SUCCEEDS_IN_CONTEXT(constraint, newline, 1, letter, 1))
	  d->states[i].constraint |= constraint;
	if (! d->states[i].first_end)
	  d->states[i].first_end = d->tokens[s->elems[j].index];
      }
    else if (d->tokens[s->elems[j].index] == BACKREF)
      {
	d->states[i].constraint = NO_CONSTRAINT;
	d->states[i].backref = 1;
      }

  ++d->sindex;

  return i;
}