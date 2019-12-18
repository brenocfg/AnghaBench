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
typedef  int /*<<< orphan*/  definition ;

/* Variables and functions */
 int /*<<< orphan*/  add_sample_msg () ; 
 int /*<<< orphan*/  checkfiles (char const*,char const*) ; 
 char const* extendfile (char const*,char const*) ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  free (char*) ; 
 long ftell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_definition () ; 
 int /*<<< orphan*/  open_input (char const*,char const*) ; 
 int /*<<< orphan*/  open_output (char const*,char const*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int /*<<< orphan*/  write_sample_svc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
svc_output(const char *infile, const char *define, int extend, const char *outfile)
{
	definition *def;
	char *include;
	const char *outfilename;
	long tell;
	open_input(infile, define);
	outfilename = extend ? extendfile(infile, outfile) : outfile;
	checkfiles(infile, outfilename);
	/*
	 * Check if outfile already exists.
	 * if so, print an error message and exit
	 */
	open_output(infile, outfilename);
	add_sample_msg();

	if (infile && (include = extendfile(infile, ".h"))) {
		f_print(fout, "#include \"%s\"\n", include);
		free(include);
	} else
		f_print(fout, "#include <rpc/rpc.h>\n");

	tell = ftell(fout);
	while ( (def = get_definition()) ) {
		write_sample_svc(def);
	}
	if (extend && tell == ftell(fout)) {
		(void) unlink(outfilename);
	}
}