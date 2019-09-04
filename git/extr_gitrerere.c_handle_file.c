#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int wrerror; void* output; int /*<<< orphan*/  getline; } ;
struct rerere_io_file {TYPE_1__ io; void* input; } ;
struct rerere_io {int dummy; } ;
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  io ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*,...) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ fclose (void*) ; 
 void* fopen (char const*,char*) ; 
 int handle_path (unsigned char*,struct rerere_io*,int) ; 
 int ll_merge_marker_size (struct index_state*,char const*) ; 
 int /*<<< orphan*/  memset (struct rerere_io_file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rerere_file_getline ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  unlink_or_warn (char const*) ; 

__attribute__((used)) static int handle_file(struct index_state *istate,
		       const char *path, unsigned char *hash, const char *output)
{
	int has_conflicts = 0;
	struct rerere_io_file io;
	int marker_size = ll_merge_marker_size(istate, path);

	memset(&io, 0, sizeof(io));
	io.io.getline = rerere_file_getline;
	io.input = fopen(path, "r");
	io.io.wrerror = 0;
	if (!io.input)
		return error_errno(_("could not open '%s'"), path);

	if (output) {
		io.io.output = fopen(output, "w");
		if (!io.io.output) {
			error_errno(_("could not write '%s'"), output);
			fclose(io.input);
			return -1;
		}
	}

	has_conflicts = handle_path(hash, (struct rerere_io *)&io, marker_size);

	fclose(io.input);
	if (io.io.wrerror)
		error(_("there were errors while writing '%s' (%s)"),
		      path, strerror(io.io.wrerror));
	if (io.io.output && fclose(io.io.output))
		io.io.wrerror = error_errno(_("failed to flush '%s'"), path);

	if (has_conflicts < 0) {
		if (output)
			unlink_or_warn(output);
		return error(_("could not parse conflict hunks in '%s'"), path);
	}
	if (io.io.wrerror)
		return -1;
	return has_conflicts;
}