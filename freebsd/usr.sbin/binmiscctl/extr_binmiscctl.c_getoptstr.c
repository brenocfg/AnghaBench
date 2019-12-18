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
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*,char const*) ; 

__attribute__((used)) static void
getoptstr(char *str, size_t size, const char *argname)
{
	if (strlen(optarg) > size)
		usage("'%s' too large", argname);
	strlcpy(str, optarg, size);
}