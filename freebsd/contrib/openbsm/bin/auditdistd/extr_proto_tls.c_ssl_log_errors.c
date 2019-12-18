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
 int /*<<< orphan*/  ERR_error_string (unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long ERR_get_error () ; 
 int /*<<< orphan*/  pjdlog_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ssl_log_errors(void)
{
	unsigned long error;

	while ((error = ERR_get_error()) != 0)
		pjdlog_error("SSL error: %s", ERR_error_string(error, NULL));
}