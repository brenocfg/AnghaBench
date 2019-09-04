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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 char* prefix_path_gently (char const*,int,int /*<<< orphan*/ *,char const*) ; 

char *prefix_path(const char *prefix, int len, const char *path)
{
	char *r = prefix_path_gently(prefix, len, NULL, path);
	if (!r)
		die(_("'%s' is outside repository"), path);
	return r;
}