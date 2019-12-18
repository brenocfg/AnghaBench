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
struct try_library_args {char const* name; int fd; int /*<<< orphan*/  buffer; int /*<<< orphan*/  buflen; int /*<<< orphan*/  namelen; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 char* path_enumerate (char const*,int /*<<< orphan*/ ,char const*,struct try_library_args*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  try_library_path ; 
 int /*<<< orphan*/  xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
search_library_path(const char *name, const char *path,
    const char *refobj_path, int *fdp)
{
    char *p;
    struct try_library_args arg;

    if (path == NULL)
	return NULL;

    arg.name = name;
    arg.namelen = strlen(name);
    arg.buffer = xmalloc(PATH_MAX);
    arg.buflen = PATH_MAX;
    arg.fd = -1;

    p = path_enumerate(path, try_library_path, refobj_path, &arg);
    *fdp = arg.fd;

    free(arg.buffer);

    return (p);
}