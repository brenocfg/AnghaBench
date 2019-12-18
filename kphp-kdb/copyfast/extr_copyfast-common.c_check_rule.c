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
struct netrule {unsigned int mask1; unsigned int ip; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int check_rule (struct netrule *A, unsigned ip) {
  assert (A->type);
  return (ip & ~(A->mask1)) == A->ip;
}