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
 int /*<<< orphan*/  assert (int*) ; 
 int /*<<< orphan*/  readin (char*,int) ; 
 int* zzmalloc0 (int) ; 

int* read_list (int l) {
  int *a = zzmalloc0 (l * sizeof (int));
  assert (a);
  readin ((char *)a, l * sizeof (int));
  return a;
}