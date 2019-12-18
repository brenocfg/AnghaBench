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
typedef  int /*<<< orphan*/  zone_t ;
typedef  int /*<<< orphan*/  z ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_ptr_zone ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zones_sort (zone_t **z, int n) {
  qsort (z, n, sizeof (z[0]), cmp_ptr_zone);
}