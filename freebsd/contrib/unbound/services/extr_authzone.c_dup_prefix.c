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
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char*
dup_prefix(char* str, size_t num)
{
	char* result;
	size_t len = strlen(str);
	if(len < num) num = len; /* not more than strlen */
	result = (char*)malloc(num+1);
	if(!result) {
		log_err("malloc failure");
		return result;
	}
	memmove(result, str, num);
	result[num] = 0;
	return result;
}