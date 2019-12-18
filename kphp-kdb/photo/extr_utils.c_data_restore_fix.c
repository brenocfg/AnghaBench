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
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  data_restore_append (int /*<<< orphan*/ *,int,int) ; 

void data_restore_fix (data *d, int a, int b, int c) {
  //assert (0);

  //b append to a
  data_restore_append (d, a, b);
  //c append to b
  data_restore_append (d, b, c);
}