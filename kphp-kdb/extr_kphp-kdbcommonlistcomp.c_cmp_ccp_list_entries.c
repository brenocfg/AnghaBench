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
struct ccp_list_entry {scalar_t__ freq; scalar_t__ leaf_value; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_ccp_list_entries (const void *a, const void *b) {
  const struct ccp_list_entry *A = (const struct ccp_list_entry *) a;
  const struct ccp_list_entry *B = (const struct ccp_list_entry *) b;
  if (A->freq < B->freq) { return -1; }
  if (A->freq > B->freq) { return 1; }
  if (A->leaf_value < B->leaf_value) { return -1; }
  if (A->leaf_value > B->leaf_value) { return 1; }
  return 0;
}