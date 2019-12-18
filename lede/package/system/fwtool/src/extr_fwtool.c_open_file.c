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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static FILE *
open_file(const char *name, bool write)
{
	FILE *ret;

	if (!strcmp(name, "-"))
		return write ? stdout : stdin;

	ret = fopen(name, write ? "w" : "r+");
	if (!ret && !write)
		ret = fopen(name, "r");

	return ret;
}