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
 int default_tuple_forward_ext (int) ; 
 int /*<<< orphan*/  tl_fetch_mark () ; 

int default_tuple_forward (int size) {
  tl_fetch_mark ();
  return default_tuple_forward_ext (size);
}