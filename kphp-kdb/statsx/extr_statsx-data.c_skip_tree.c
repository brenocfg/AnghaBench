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
 scalar_t__ readin_char () ; 
 int /*<<< orphan*/  readin_int () ; 

void skip_tree (void) {
  if (readin_char () == 0) {
    return;
  }
  readin_int ();
  readin_int ();
  skip_tree ();
  skip_tree ();
}