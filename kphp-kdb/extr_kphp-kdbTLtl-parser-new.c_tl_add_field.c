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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fields ; 
 int /*<<< orphan*/  lrand48 () ; 
 int namespace_level ; 
 int /*<<< orphan*/  tree_insert_tl_field (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_lookup_tl_field (int /*<<< orphan*/ ,char*) ; 

int tl_add_field (char *id) {
  assert (namespace_level < 10);
  assert (namespace_level >= 0);
  if (tree_lookup_tl_field (fields[namespace_level], id)) {
    return 0;
  }
  fields[namespace_level] = tree_insert_tl_field (fields[namespace_level], id, lrand48 ());
  return 1;
}