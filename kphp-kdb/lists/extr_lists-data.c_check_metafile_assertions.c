#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ flags; scalar_t__ tot_entries; } ;
typedef  TYPE_1__ metafile_t ;
typedef  int /*<<< orphan*/  list_id_t ;
struct TYPE_9__ {scalar_t__ flags; } ;
struct TYPE_8__ {int tot_lists; } ;

/* Variables and functions */
 scalar_t__ FILE_LIST_MAGIC ; 
 TYPE_6__* FLI_ENTRY_ADJUSTED (int) ; 
 TYPE_5__ Header ; 
 unsigned int MAX_METAFILE_ENTRIES ; 
 int /*<<< orphan*/  MF_LIST_ID (TYPE_1__*) ; 
 scalar_t__ MF_MAGIC (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* get_metafile_ptr (int) ; 
 scalar_t__ list_id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int check_metafile_assertions (list_id_t list_id, int l) {
  assert (0 <= l && l < Header.tot_lists);
  metafile_t *M = get_metafile_ptr (l);
  assert (MF_MAGIC(M) == FILE_LIST_MAGIC && list_id_equal (MF_LIST_ID(M), list_id));
  assert (M->flags == FLI_ENTRY_ADJUSTED(l)->flags);
  assert ((unsigned) M->tot_entries <= MAX_METAFILE_ENTRIES);
  return 0;
}