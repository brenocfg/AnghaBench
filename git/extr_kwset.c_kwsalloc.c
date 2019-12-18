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
struct trie {scalar_t__ shift; scalar_t__ depth; int /*<<< orphan*/ * fail; int /*<<< orphan*/ * next; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * links; scalar_t__ accepting; } ;
struct kwset {int maxd; unsigned char const* trans; int /*<<< orphan*/ * target; int /*<<< orphan*/  mind; struct trie* trie; int /*<<< orphan*/  obstack; scalar_t__ words; } ;
typedef  int /*<<< orphan*/ * kwset_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  kwsfree (int /*<<< orphan*/ *) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obstack_init (int /*<<< orphan*/ *) ; 
 scalar_t__ xmalloc (int) ; 

kwset_t
kwsalloc (unsigned char const *trans)
{
  struct kwset *kwset;

  kwset = (struct kwset *) xmalloc(sizeof (struct kwset));

  obstack_init(&kwset->obstack);
  kwset->words = 0;
  kwset->trie
    = (struct trie *) obstack_alloc(&kwset->obstack, sizeof (struct trie));
  if (!kwset->trie)
    {
      kwsfree((kwset_t) kwset);
      return NULL;
    }
  kwset->trie->accepting = 0;
  kwset->trie->links = NULL;
  kwset->trie->parent = NULL;
  kwset->trie->next = NULL;
  kwset->trie->fail = NULL;
  kwset->trie->depth = 0;
  kwset->trie->shift = 0;
  kwset->mind = INT_MAX;
  kwset->maxd = -1;
  kwset->target = NULL;
  kwset->trans = trans;

  return (kwset_t) kwset;
}