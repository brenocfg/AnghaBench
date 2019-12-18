#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ADD_SIZET_OVERFLOW (size_t*,size_t,int) ; 
 TYPE_1__* git__realloc (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 

git_reference *git_reference__set_name(
	git_reference *ref, const char *name)
{
	size_t namelen = strlen(name);
	size_t reflen;
	git_reference *rewrite = NULL;

	if (!GIT_ADD_SIZET_OVERFLOW(&reflen, sizeof(git_reference), namelen) &&
		!GIT_ADD_SIZET_OVERFLOW(&reflen, reflen, 1) &&
		(rewrite = git__realloc(ref, reflen)) != NULL)
		memcpy(rewrite->name, name, namelen + 1);

	return rewrite;
}