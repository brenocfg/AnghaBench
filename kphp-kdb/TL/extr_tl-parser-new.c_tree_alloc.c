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
struct tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct tree*) ; 
 int /*<<< orphan*/  memset (struct tree*,int /*<<< orphan*/ ,int) ; 
 struct tree* zmalloc (int) ; 

struct tree *tree_alloc (void) {
  struct tree *T = zmalloc (sizeof (*T));
  assert (T);
  memset (T, 0, sizeof (*T));
  return T;
}