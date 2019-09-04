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
 int /*<<< orphan*/  diagonal_gather_methods ; 
 int /*<<< orphan*/  diagonal_queries ; 
 int /*<<< orphan*/  merge_forward (int /*<<< orphan*/ *) ; 

int default_query_diagonal_forward (void) {
  diagonal_queries ++;
  merge_forward (&diagonal_gather_methods);
  return 0;
}