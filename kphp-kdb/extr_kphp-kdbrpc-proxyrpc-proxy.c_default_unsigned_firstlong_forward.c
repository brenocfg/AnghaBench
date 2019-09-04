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
 int default_unsigned_firstlong_forward_ext () ; 
 int /*<<< orphan*/  tl_fetch_mark () ; 

int default_unsigned_firstlong_forward (void) {
  tl_fetch_mark ();
  return default_unsigned_firstlong_forward_ext ();
}