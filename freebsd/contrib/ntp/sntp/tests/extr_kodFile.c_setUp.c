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
 int /*<<< orphan*/  init_lib () ; 
 int /*<<< orphan*/ * kod_db ; 
 scalar_t__ kod_db_cnt ; 

void
setUp(void) {
	kod_db_cnt = 0;
	kod_db = NULL;
	init_lib();
}