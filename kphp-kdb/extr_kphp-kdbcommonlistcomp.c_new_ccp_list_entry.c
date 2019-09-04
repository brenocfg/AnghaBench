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
struct ccp_list_entry {long long freq; int /*<<< orphan*/ * next; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;

/* Variables and functions */
 struct ccp_list_entry* zmalloc (int) ; 

__attribute__((used)) static struct ccp_list_entry *new_ccp_list_entry (long long freq) {
  struct ccp_list_entry *x = zmalloc (sizeof (struct ccp_list_entry));
  x->freq = freq;
  x->left = x->right = x->next = NULL;
  return x;
}