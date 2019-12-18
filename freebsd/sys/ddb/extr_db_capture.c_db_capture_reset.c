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
 scalar_t__ db_capture_bufoff ; 
 scalar_t__ db_capture_bufpadding ; 
 scalar_t__ db_capture_inprogress ; 

__attribute__((used)) static void
db_capture_reset(void)
{

	db_capture_inprogress = 0;
	db_capture_bufoff = 0;
	db_capture_bufpadding = 0;
}