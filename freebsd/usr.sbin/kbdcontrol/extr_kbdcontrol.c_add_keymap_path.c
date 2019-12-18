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
struct pathent {char* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pathent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  pathlist ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
add_keymap_path(const char *path)
{
	struct pathent* pe;
	size_t len;

	len = strlen(path);
	if ((pe = malloc(sizeof(*pe))) == NULL ||
	    (pe->path = malloc(len + 2)) == NULL)
		err(1, "malloc");
	memcpy(pe->path, path, len);
	if (len > 0 && path[len - 1] != '/')
		pe->path[len++] = '/';
	pe->path[len] = '\0';
	STAILQ_INSERT_TAIL(&pathlist, pe, next);
}