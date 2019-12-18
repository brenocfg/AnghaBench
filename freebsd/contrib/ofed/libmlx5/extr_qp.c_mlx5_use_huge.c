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
 char* getenv (char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int mlx5_use_huge(const char *key)
{
	char *e;
	e = getenv(key);
	if (e && !strcmp(e, "y"))
		return 1;

	return 0;
}