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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int off_t ;

/* Variables and functions */
 char* prefixes ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int /*<<< orphan*/ ,char const) ; 

__attribute__((used)) static void
stat_bytes(char *str, size_t strsz, off_t bytes)
{
	const char *prefix = prefixes;

	while (bytes > 9999 && prefix[1] != '\0') {
		bytes /= 1024;
		prefix++;
	}
	snprintf(str, strsz, "%4ju %cB", (uintmax_t)bytes, *prefix);
}