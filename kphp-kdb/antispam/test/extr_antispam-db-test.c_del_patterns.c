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
 int N ; 
 int* _id ; 
 int /*<<< orphan*/  antispam_del (int) ; 
 double current_time () ; 
 int /*<<< orphan*/  dyn_free_bytes () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,...) ; 
 int /*<<< orphan*/  memory_statistic () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void del_patterns (void) {
  int i;
  fprintf (stderr, "[%6.2f] Del all patterns... [free bytes = %ld] ", current_time(), dyn_free_bytes());
  for (i = 0; i < N; i++) {
    antispam_del (_id[i]);
  }

  // Try to del inexisting pattern
  // Suppose that there is no such id in trie
  antispam_del (178537843);

  fprintf (stderr, "OK [free bytes = %ld]\n", dyn_free_bytes());
  memory_statistic();
}