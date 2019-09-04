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
struct tl_type {int constructors_num; int /*<<< orphan*/ * constructors; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_constructor (int /*<<< orphan*/ ) ; 

void write_type_constructors (struct tl_type *t) {
  int i;
  for (i = 0; i < t->constructors_num; i++) {
    write_constructor (t->constructors[i]);
  }
}