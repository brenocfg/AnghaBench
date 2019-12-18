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
 int /*<<< orphan*/  db_flush_line () ; 
 scalar_t__ db_look_char ; 
 scalar_t__ db_look_token ; 

void
db_flush_lex(void)
{
	db_flush_line();
	db_look_char = 0;
	db_look_token = 0;
}