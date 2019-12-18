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
struct trie {scalar_t__ shift; scalar_t__ depth; scalar_t__ fail; scalar_t__ next; scalar_t__ parent; scalar_t__ links; scalar_t__ accepting; } ;
struct kwset {int maxd; char const* trans; scalar_t__ target; int /*<<< orphan*/  mind; struct trie* trie; int /*<<< orphan*/  obstack; scalar_t__ words; } ;
typedef  int /*<<< orphan*/  kwset_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  kwsfree (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obstack_init (int /*<<< orphan*/ *) ; 

kwset_t
kwsalloc (char const *trans)
{
  struct kwset *kwset;

  kwset = (struct kwset *) malloc(sizeof (struct kwset));
  if (!kwset)
    return 0;

  obstack_init(&kwset->obstack);
  kwset->words = 0;
  kwset->trie
    = (struct trie *) obstack_alloc(&kwset->obstack, sizeof (struct trie));
  if (!kwset->trie)
    {
      kwsfree((kwset_t) kwset);
      return 0;
    }
  kwset->trie->accepting = 0;
  kwset->trie->links = 0;
  kwset->trie->parent = 0;
  kwset->trie->next = 0;
  kwset->trie->fail = 0;
  kwset->trie->depth = 0;
  kwset->trie->shift = 0;
  kwset->mind = INT_MAX;
  kwset->maxd = -1;
  kwset->target = 0;
  kwset->trans = trans;

  return (kwset_t) kwset;
}