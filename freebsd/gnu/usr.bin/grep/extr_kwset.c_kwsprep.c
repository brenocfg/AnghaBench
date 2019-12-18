#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct trie {int shift; int maxshift; scalar_t__ depth; TYPE_2__* links; TYPE_1__* parent; struct trie* next; scalar_t__ accepting; struct trie* fail; } ;
struct kwset {int mind; int words; char* trans; scalar_t__* target; int mind2; unsigned char* delta; struct trie** next; struct trie* trie; int /*<<< orphan*/  obstack; } ;
typedef  scalar_t__ kwset_t ;
struct TYPE_9__ {scalar_t__ label; struct trie* trie; } ;
struct TYPE_8__ {scalar_t__ maxshift; } ;

/* Variables and functions */
 int NCHAR ; 
 int /*<<< orphan*/  enqueue (TYPE_2__*,struct trie**) ; 
 int /*<<< orphan*/  hasevery (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__* obstack_alloc (int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  treedelta (TYPE_2__*,scalar_t__,unsigned char*) ; 
 int /*<<< orphan*/  treefails (TYPE_2__*,struct trie*,struct trie*) ; 
 int /*<<< orphan*/  treenext (TYPE_2__*,struct trie**) ; 

char *
kwsprep (kwset_t kws)
{
  register struct kwset *kwset;
  register int i;
  register struct trie *curr, *fail;
  register char const *trans;
  unsigned char delta[NCHAR];
  struct trie *last, *next[NCHAR];

  kwset = (struct kwset *) kws;

  /* Initial values for the delta table; will be changed later.  The
     delta entry for a given character is the smallest depth of any
     node at which an outgoing edge is labeled by that character. */
  if (kwset->mind < 256)
    for (i = 0; i < NCHAR; ++i)
      delta[i] = kwset->mind;
  else
    for (i = 0; i < NCHAR; ++i)
      delta[i] = 255;

  /* Check if we can use the simple boyer-moore algorithm, instead
     of the hairy commentz-walter algorithm. */
  if (kwset->words == 1 && kwset->trans == 0)
    {
      /* Looking for just one string.  Extract it from the trie. */
      kwset->target = obstack_alloc(&kwset->obstack, kwset->mind);
      for (i = kwset->mind - 1, curr = kwset->trie; i >= 0; --i)
	{
	  kwset->target[i] = curr->links->label;
	  curr = curr->links->trie;
	}
      /* Build the Boyer Moore delta.  Boy that's easy compared to CW. */
      for (i = 0; i < kwset->mind; ++i)
	delta[(unsigned char) kwset->target[i]] = kwset->mind - (i + 1);
      kwset->mind2 = kwset->mind;
      /* Find the minimal delta2 shift that we might make after
	 a backwards match has failed. */
      for (i = 0; i < kwset->mind - 1; ++i)
	if (kwset->target[i] == kwset->target[kwset->mind - 1])
	  kwset->mind2 = kwset->mind - (i + 1);
    }
  else
    {
      /* Traverse the nodes of the trie in level order, simultaneously
	 computing the delta table, failure function, and shift function. */
      for (curr = last = kwset->trie; curr; curr = curr->next)
	{
	  /* Enqueue the immediate descendents in the level order queue. */
	  enqueue(curr->links, &last);

	  curr->shift = kwset->mind;
	  curr->maxshift = kwset->mind;

	  /* Update the delta table for the descendents of this node. */
	  treedelta(curr->links, curr->depth, delta);

	  /* Compute the failure function for the decendents of this node. */
	  treefails(curr->links, curr->fail, kwset->trie);

	  /* Update the shifts at each node in the current node's chain
	     of fails back to the root. */
	  for (fail = curr->fail; fail; fail = fail->fail)
	    {
	      /* If the current node has some outgoing edge that the fail
		 doesn't, then the shift at the fail should be no larger
		 than the difference of their depths. */
	      if (!hasevery(fail->links, curr->links))
		if (curr->depth - fail->depth < fail->shift)
		  fail->shift = curr->depth - fail->depth;

	      /* If the current node is accepting then the shift at the
		 fail and its descendents should be no larger than the
		 difference of their depths. */
	      if (curr->accepting && fail->maxshift > curr->depth - fail->depth)
		fail->maxshift = curr->depth - fail->depth;
	    }
	}

      /* Traverse the trie in level order again, fixing up all nodes whose
	 shift exceeds their inherited maxshift. */
      for (curr = kwset->trie->next; curr; curr = curr->next)
	{
	  if (curr->maxshift > curr->parent->maxshift)
	    curr->maxshift = curr->parent->maxshift;
	  if (curr->shift > curr->maxshift)
	    curr->shift = curr->maxshift;
	}

      /* Create a vector, indexed by character code, of the outgoing links
	 from the root node. */
      for (i = 0; i < NCHAR; ++i)
	next[i] = 0;
      treenext(kwset->trie->links, next);

      if ((trans = kwset->trans) != 0)
	for (i = 0; i < NCHAR; ++i)
	  kwset->next[i] = next[(unsigned char) trans[i]];
      else
	for (i = 0; i < NCHAR; ++i)
	  kwset->next[i] = next[i];
    }

  /* Fix things up for any translation table. */
  if ((trans = kwset->trans) != 0)
    for (i = 0; i < NCHAR; ++i)
      kwset->delta[i] = delta[(unsigned char) trans[i]];
  else
    for (i = 0; i < NCHAR; ++i)
      kwset->delta[i] = delta[i];

  return 0;
}