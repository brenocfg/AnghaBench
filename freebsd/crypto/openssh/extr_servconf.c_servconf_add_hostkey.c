#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  num_host_key_files; int /*<<< orphan*/  host_key_files; } ;
typedef  TYPE_1__ ServerOptions ;

/* Variables and functions */
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_append (char const*,int const,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 char const* defaultkey ; 
 char* derelativise_path (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 

void
servconf_add_hostkey(const char *file, const int line,
    ServerOptions *options, const char *path)
{
	char *apath = derelativise_path(path);

	if (file == defaultkey && access(path, R_OK) != 0)
		return;
	array_append(file, line, "HostKey",
	    &options->host_key_files, &options->num_host_key_files, apath);
	free(apath);
}