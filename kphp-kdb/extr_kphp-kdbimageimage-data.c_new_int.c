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
struct stack_entry {int /*<<< orphan*/  tp; int /*<<< orphan*/  a; } ;

/* Variables and functions */
 int /*<<< orphan*/  ft_int ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void new_int (struct stack_entry *E, int i) {
  memcpy (&E->a, &i, 4);
  E->tp = ft_int;
}