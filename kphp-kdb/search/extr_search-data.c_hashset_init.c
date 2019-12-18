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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hashset_ll_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hs ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void hashset_init (int n) {
  if (!hashset_ll_init (&hs, n)) {
    fprintf (stderr, "Could allocate hashset_ll, n = %d\n", n);
    exit (2);
  }
}