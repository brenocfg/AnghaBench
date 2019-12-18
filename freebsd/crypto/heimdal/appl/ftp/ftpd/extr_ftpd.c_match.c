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
 int /*<<< orphan*/  FNM_NOESCAPE ; 
 int fnmatch (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
match(const char *pattern, const char *string)
{
    return fnmatch(pattern, string, FNM_NOESCAPE);
}