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
struct TYPE_3__ {scalar_t__ def_kind; } ;
typedef  TYPE_1__ definition ;

/* Variables and functions */
 scalar_t__ DEF_PROGRAM ; 
 int /*<<< orphan*/  add_warning () ; 
 char const* extendfile (char const*,char const*) ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* get_definition () ; 
 int /*<<< orphan*/  open_input (char const*,char const*) ; 
 int /*<<< orphan*/  open_output (char const*,char const*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int /*<<< orphan*/  write_stubs () ; 

__attribute__((used)) static void
l_output(const char *infile, const char *define, int extend, const char *outfile)
{
	char *include;
	definition *def;
	int foundprogram = 0;
	const char *outfilename;

	open_input(infile, define);
	outfilename = extend ? extendfile(infile, outfile) : outfile;
	open_output(infile, outfilename);
	add_warning();
	f_print (fout, "#include <string.h> /* for memset */\n");
	if (infile && (include = extendfile(infile, ".h"))) {
		f_print(fout, "#include \"%s\"\n", include);
		free(include);
	} else
		f_print(fout, "#include <rpc/rpc.h>\n");
	while ( (def = get_definition()) ) {
		foundprogram |= (def->def_kind == DEF_PROGRAM);
	}
	if (extend && !foundprogram) {
		(void) unlink(outfilename);
		return;
	}
	write_stubs();
}