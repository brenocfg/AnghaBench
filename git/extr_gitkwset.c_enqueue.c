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
struct trie {struct trie* next; } ;
struct tree {struct trie* trie; struct tree* rlink; struct tree* llink; } ;

/* Variables and functions */

__attribute__((used)) static void
enqueue (struct tree *tree, struct trie **last)
{
  if (!tree)
    return;
  enqueue(tree->llink, last);
  enqueue(tree->rlink, last);
  (*last) = (*last)->next = tree->trie;
}