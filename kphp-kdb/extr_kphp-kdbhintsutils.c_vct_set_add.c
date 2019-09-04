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
typedef  int /*<<< orphan*/  vector ;

/* Variables and functions */
 int /*<<< orphan*/  vct_add (int /*<<< orphan*/ *,int) ; 
 int vct_back (int /*<<< orphan*/ *) ; 

void vct_set_add (vector *v, int val) {
  if (vct_back (v) != val) {
    vct_add (v, val);
  }
}