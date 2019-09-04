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
struct gather {int /*<<< orphan*/ * methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  gather_do_nothing_methods ; 

void merge_terminate_gather (struct gather *G) {
  G->methods = &gather_do_nothing_methods;
}