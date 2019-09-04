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
typedef  int /*<<< orphan*/  iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  build_binary_subtraction_iterator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_everything_iterator () ; 

iterator_t build_complement_iterator (iterator_t A) {
  return build_binary_subtraction_iterator (build_everything_iterator (), A);
}