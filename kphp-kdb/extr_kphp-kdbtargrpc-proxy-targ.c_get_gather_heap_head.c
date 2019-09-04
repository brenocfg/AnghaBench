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
typedef  int /*<<< orphan*/  gh_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** GH ; 
 scalar_t__ GH_N ; 

__attribute__((used)) static gh_entry_t *get_gather_heap_head (void) {
  return GH_N ? GH[1] : 0;
}