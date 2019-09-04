#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* attributes; int /*<<< orphan*/  apply; int /*<<< orphan*/  shutdown; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ git_filter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILTER_VERSION ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_filter_free ; 
 int /*<<< orphan*/  ident_apply ; 

git_filter *git_ident_filter_new(void)
{
	git_filter *f = git__calloc(1, sizeof(git_filter));
	if (f == NULL)
		return NULL;

	f->version = GIT_FILTER_VERSION;
	f->attributes = "+ident"; /* apply to files with ident attribute set */
	f->shutdown = git_filter_free;
	f->apply    = ident_apply;

	return f;
}