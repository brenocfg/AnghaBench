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
 int ENOENT ; 
 int RTAS_UNKNOWN_SERVICE ; 
 scalar_t__ rtas_busy_delay (int) ; 
 int rtas_call (int,int,int,int /*<<< orphan*/ *,int,int,int) ; 
 int rtas_error_rc (int) ; 
 int rtas_token (char*) ; 

int rtas_set_indicator(int indicator, int index, int new_value)
{
	int token = rtas_token("set-indicator");
	int rc;

	if (token == RTAS_UNKNOWN_SERVICE)
		return -ENOENT;

	do {
		rc = rtas_call(token, 3, 1, NULL, indicator, index, new_value);
	} while (rtas_busy_delay(rc));

	if (rc < 0)
		return rtas_error_rc(rc);
	return rc;
}