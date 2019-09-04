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
 unsigned int REF_HEADS ; 
 unsigned int REF_NORMAL ; 
 unsigned int REF_TAGS ; 
 scalar_t__ check_refname_format (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 

__attribute__((used)) static int check_ref(const char *name, unsigned int flags)
{
	if (!flags)
		return 1;

	if (!skip_prefix(name, "refs/", &name))
		return 0;

	/* REF_NORMAL means that we don't want the magic fake tag refs */
	if ((flags & REF_NORMAL) && check_refname_format(name, 0))
		return 0;

	/* REF_HEADS means that we want regular branch heads */
	if ((flags & REF_HEADS) && starts_with(name, "heads/"))
		return 1;

	/* REF_TAGS means that we want tags */
	if ((flags & REF_TAGS) && starts_with(name, "tags/"))
		return 1;

	/* All type bits clear means that we are ok with anything */
	return !(flags & ~REF_NORMAL);
}