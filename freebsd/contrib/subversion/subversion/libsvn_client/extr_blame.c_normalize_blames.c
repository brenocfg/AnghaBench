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
struct blame_chain {struct blame* blame; } ;
struct blame {scalar_t__ start; struct blame* next; int /*<<< orphan*/  rev; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct blame* blame_create (struct blame_chain*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
normalize_blames(struct blame_chain *chain,
                 struct blame_chain *chain_merged,
                 apr_pool_t *pool)
{
  struct blame *walk, *walk_merged;

  /* Walk over the CHAIN's blame chunks and CHAIN_MERGED's blame chunks,
     creating new chunks as needed. */
  for (walk = chain->blame, walk_merged = chain_merged->blame;
       walk->next && walk_merged->next;
       walk = walk->next, walk_merged = walk_merged->next)
    {
      /* The current chunks should always be starting at the same offset. */
      assert(walk->start == walk_merged->start);

      if (walk->next->start < walk_merged->next->start)
        {
          /* insert a new chunk in CHAIN_MERGED. */
          struct blame *tmp = blame_create(chain_merged, walk_merged->rev,
                                           walk->next->start);
          tmp->next = walk_merged->next;
          walk_merged->next = tmp;
        }

      if (walk->next->start > walk_merged->next->start)
        {
          /* insert a new chunk in CHAIN. */
          struct blame *tmp = blame_create(chain, walk->rev,
                                           walk_merged->next->start);
          tmp->next = walk->next;
          walk->next = tmp;
        }
    }

  /* If both NEXT pointers are null, the lists are equally long, otherwise
     we need to extend one of them.  If CHAIN is longer, append new chunks
     to CHAIN_MERGED until its length matches that of CHAIN. */
  while (walk->next != NULL)
    {
      struct blame *tmp = blame_create(chain_merged, walk_merged->rev,
                                       walk->next->start);
      walk_merged->next = tmp;

      walk_merged = walk_merged->next;
      walk = walk->next;
    }

  /* Same as above, only extend CHAIN to match CHAIN_MERGED. */
  while (walk_merged->next != NULL)
    {
      struct blame *tmp = blame_create(chain, walk->rev,
                                       walk_merged->next->start);
      walk->next = tmp;

      walk = walk->next;
      walk_merged = walk_merged->next;
    }
}