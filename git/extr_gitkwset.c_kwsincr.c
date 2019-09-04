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
struct trie {int accepting; scalar_t__ depth; scalar_t__ shift; int /*<<< orphan*/ * fail; int /*<<< orphan*/ * next; struct trie* parent; struct tree* links; } ;
struct tree {unsigned char label; int balance; struct trie* trie; struct tree* rlink; struct tree* llink; } ;
struct kwset {char const* trans; int words; scalar_t__ mind; scalar_t__ maxd; int /*<<< orphan*/  obstack; struct trie* trie; } ;
typedef  scalar_t__ kwset_t ;

/* Variables and functions */
 int DEPTH_SIZE ; 
 size_t U (char const) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,struct tree*) ; 

const char *
kwsincr (kwset_t kws, char const *text, size_t len)
{
  struct kwset *kwset;
  register struct trie *trie;
  register unsigned char label;
  register struct tree *link;
  register int depth;
  struct tree *links[DEPTH_SIZE];
  enum { L, R } dirs[DEPTH_SIZE];
  struct tree *t, *r, *l, *rl, *lr;

  kwset = (struct kwset *) kws;
  trie = kwset->trie;
  text += len;

  /* Descend the trie (built of reversed keywords) character-by-character,
     installing new nodes when necessary. */
  while (len--)
    {
      label = kwset->trans ? kwset->trans[U(*--text)] : *--text;

      /* Descend the tree of outgoing links for this trie node,
	 looking for the current character and keeping track
	 of the path followed. */
      link = trie->links;
      links[0] = (struct tree *) &trie->links;
      dirs[0] = L;
      depth = 1;

      while (link && label != link->label)
	{
	  links[depth] = link;
	  if (label < link->label)
	    dirs[depth++] = L, link = link->llink;
	  else
	    dirs[depth++] = R, link = link->rlink;
	}

      /* The current character doesn't have an outgoing link at
	 this trie node, so build a new trie node and install
	 a link in the current trie node's tree. */
      if (!link)
	{
	  link = (struct tree *) obstack_alloc(&kwset->obstack,
					       sizeof (struct tree));
	  if (!link)
	    return "memory exhausted";
	  link->llink = NULL;
	  link->rlink = NULL;
	  link->trie = (struct trie *) obstack_alloc(&kwset->obstack,
						     sizeof (struct trie));
	  if (!link->trie)
	    {
	      obstack_free(&kwset->obstack, link);
	      return "memory exhausted";
	    }
	  link->trie->accepting = 0;
	  link->trie->links = NULL;
	  link->trie->parent = trie;
	  link->trie->next = NULL;
	  link->trie->fail = NULL;
	  link->trie->depth = trie->depth + 1;
	  link->trie->shift = 0;
	  link->label = label;
	  link->balance = 0;

	  /* Install the new tree node in its parent. */
	  if (dirs[--depth] == L)
	    links[depth]->llink = link;
	  else
	    links[depth]->rlink = link;

	  /* Back up the tree fixing the balance flags. */
	  while (depth && !links[depth]->balance)
	    {
	      if (dirs[depth] == L)
		--links[depth]->balance;
	      else
		++links[depth]->balance;
	      --depth;
	    }

	  /* Rebalance the tree by pointer rotations if necessary. */
	  if (depth && ((dirs[depth] == L && --links[depth]->balance)
			|| (dirs[depth] == R && ++links[depth]->balance)))
	    {
	      switch (links[depth]->balance)
		{
		case (char) -2:
		  switch (dirs[depth + 1])
		    {
		    case L:
		      r = links[depth], t = r->llink, rl = t->rlink;
		      t->rlink = r, r->llink = rl;
		      t->balance = r->balance = 0;
		      break;
		    case R:
		      r = links[depth], l = r->llink, t = l->rlink;
		      rl = t->rlink, lr = t->llink;
		      t->llink = l, l->rlink = lr, t->rlink = r, r->llink = rl;
		      l->balance = t->balance != 1 ? 0 : -1;
		      r->balance = t->balance != (char) -1 ? 0 : 1;
		      t->balance = 0;
		      break;
		    default:
		      abort ();
		    }
		  break;
		case 2:
		  switch (dirs[depth + 1])
		    {
		    case R:
		      l = links[depth], t = l->rlink, lr = t->llink;
		      t->llink = l, l->rlink = lr;
		      t->balance = l->balance = 0;
		      break;
		    case L:
		      l = links[depth], r = l->rlink, t = r->llink;
		      lr = t->llink, rl = t->rlink;
		      t->llink = l, l->rlink = lr, t->rlink = r, r->llink = rl;
		      l->balance = t->balance != 1 ? 0 : -1;
		      r->balance = t->balance != (char) -1 ? 0 : 1;
		      t->balance = 0;
		      break;
		    default:
		      abort ();
		    }
		  break;
		default:
		  abort ();
		}

	      if (dirs[depth - 1] == L)
		links[depth - 1]->llink = t;
	      else
		links[depth - 1]->rlink = t;
	    }
	}

      trie = link->trie;
    }

  /* Mark the node we finally reached as accepting, encoding the
     index number of this word in the keyword set so far. */
  if (!trie->accepting)
    trie->accepting = 1 + 2 * kwset->words;
  ++kwset->words;

  /* Keep track of the longest and shortest string of the keyword set. */
  if (trie->depth < kwset->mind)
    kwset->mind = trie->depth;
  if (trie->depth > kwset->maxd)
    kwset->maxd = trie->depth;

  return NULL;
}