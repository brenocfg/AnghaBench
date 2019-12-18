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
 int /*<<< orphan*/  log_err (char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char*
dup_all(char* str)
{
	char* result = strdup(str);
	if(!result) {
		log_err("malloc failure");
		return NULL;
	}
	return result;
}