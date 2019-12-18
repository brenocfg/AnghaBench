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
 int /*<<< orphan*/  db_flush_lex () ; 
 int /*<<< orphan*/  db_printf (char*,char const*) ; 
 int /*<<< orphan*/  kdb_reenter_silent () ; 

void
db_error(const char *s)
{
	if (s)
	    db_printf("%s", s);
	db_flush_lex();
	kdb_reenter_silent();
}