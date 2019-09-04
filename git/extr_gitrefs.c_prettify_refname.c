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
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 

const char *prettify_refname(const char *name)
{
	if (skip_prefix(name, "refs/heads/", &name) ||
	    skip_prefix(name, "refs/tags/", &name) ||
	    skip_prefix(name, "refs/remotes/", &name))
		; /* nothing */
	return name;
}