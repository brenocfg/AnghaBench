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
struct iterator {int dummy; } ;
typedef  int /*<<< orphan*/  iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  init_empty_iterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmalloc (int) ; 

iterator_t build_empty_iterator (void) {
  iterator_t I = zmalloc (sizeof (struct iterator));
  init_empty_iterator (I);
  return I;
}