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
 scalar_t__ cgetstr (int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  confbuf ; 
 scalar_t__ login_conf_init () ; 

char *
login_conf_get_string(const char *str)
{
    char *value;
    if(login_conf_init() != 0)
	return NULL;
    if(cgetstr(confbuf, (char *)str, &value) < 0)
	return NULL;
    return value;
}