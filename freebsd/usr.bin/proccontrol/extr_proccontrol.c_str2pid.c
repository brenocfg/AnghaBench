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
typedef  int pid_t ;

/* Variables and functions */
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static pid_t
str2pid(const char *str)
{
	pid_t res;
	char *tail;

	res = strtol(str, &tail, 0);
	if (*tail != '\0') {
		warnx("non-numeric pid");
		return (-1);
	}
	return (res);
}