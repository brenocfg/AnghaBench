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
 char* appname ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/ * listfile ; 
 char* listfilename ; 
 int /*<<< orphan*/ * ofile ; 
 char* ofilename ; 
 int /*<<< orphan*/  patch_functions ; 
 int /*<<< orphan*/ * regfile ; 
 char* regfilename ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  symlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symtable_close () ; 
 int /*<<< orphan*/  unlink (char*) ; 
 char* yyfilename ; 
 int yylineno ; 

void
stop(const char *string, int err_code)
{
	if (string != NULL) {
		fprintf(stderr, "%s: ", appname);
		if (yyfilename != NULL) {
			fprintf(stderr, "Stopped at file %s, line %d - ",
				yyfilename, yylineno);
		}
		fprintf(stderr, "%s\n", string);
	}

	if (ofile != NULL) {
		fclose(ofile);
		if (err_code != 0) {
			fprintf(stderr, "%s: Removing %s due to error\n",
				appname, ofilename);
			unlink(ofilename);
		}
	}

	if (regfile != NULL) {
		fclose(regfile);
		if (err_code != 0) {
			fprintf(stderr, "%s: Removing %s due to error\n",
				appname, regfilename);
			unlink(regfilename);
		}
	}

	if (listfile != NULL) {
		fclose(listfile);
		if (err_code != 0) {
			fprintf(stderr, "%s: Removing %s due to error\n",
				appname, listfilename);
			unlink(listfilename);
		}
	}

	symlist_free(&patch_functions);
	symtable_close();

	exit(err_code);
}