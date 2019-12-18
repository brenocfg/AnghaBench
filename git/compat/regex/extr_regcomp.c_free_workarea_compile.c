#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ buffer; } ;
typedef  TYPE_1__ regex_t ;
struct TYPE_7__ {TYPE_3__* org_indices; int /*<<< orphan*/ * str_tree; int /*<<< orphan*/  str_tree_storage_idx; TYPE_3__* str_tree_storage; } ;
typedef  TYPE_2__ re_dfa_t ;
struct TYPE_8__ {struct TYPE_8__* next; } ;
typedef  TYPE_3__ bin_tree_storage_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIN_TREE_STORAGE_SIZE ; 
 int /*<<< orphan*/  re_free (TYPE_3__*) ; 

__attribute__((used)) static void
free_workarea_compile (regex_t *preg)
{
  re_dfa_t *dfa = (re_dfa_t *) preg->buffer;
  bin_tree_storage_t *storage, *next;
  for (storage = dfa->str_tree_storage; storage; storage = next)
    {
      next = storage->next;
      re_free (storage);
    }
  dfa->str_tree_storage = NULL;
  dfa->str_tree_storage_idx = BIN_TREE_STORAGE_SIZE;
  dfa->str_tree = NULL;
  re_free (dfa->org_indices);
  dfa->org_indices = NULL;
}