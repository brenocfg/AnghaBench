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
 char* error_last_message () ; 
 int /*<<< orphan*/  mi_error_message ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void
mi_error_last_message (void)
{
  char *s = error_last_message ();
  xasprintf (&mi_error_message, "%s", s);
  xfree (s);
}