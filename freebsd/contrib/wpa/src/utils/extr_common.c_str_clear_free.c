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
 int /*<<< orphan*/  forced_memzero (char*,size_t) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 size_t os_strlen (char*) ; 

void str_clear_free(char *str)
{
	if (str) {
		size_t len = os_strlen(str);
		forced_memzero(str, len);
		os_free(str);
	}
}