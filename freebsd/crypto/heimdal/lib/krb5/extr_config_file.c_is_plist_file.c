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
typedef  int /*<<< orphan*/  suffix ;

/* Variables and functions */
 scalar_t__ strcasecmp (char const*,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int
is_plist_file(const char *fname)
{
    size_t len = strlen(fname);
    char suffix[] = ".plist";
    if (len < sizeof(suffix))
	return 0;
    if (strcasecmp(&fname[len - (sizeof(suffix) - 1)], suffix) != 0)
	return 0;
    return 1;
}