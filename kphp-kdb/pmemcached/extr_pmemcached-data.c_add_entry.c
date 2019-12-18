#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  local_clock () ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  total_items ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  tree_insert (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int verbosity ; 

void add_entry (hash_entry_t *entry) {
  if (verbosity >= 4) {
    fprintf (stderr, "add_entry (%p)\n", entry);
  }
  assert (entry);
  //assert (0 <= x && x < MAX_HASH_TABLE_SIZE + TIME_TABLE_SIZE + 1);


  entry->timestamp = local_clock ();
  tree = tree_insert (tree, entry, lrand48 ());
  total_items++;
}