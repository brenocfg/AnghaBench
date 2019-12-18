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
struct error_code {int number; char* string; struct error_code* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  cfn ; 
 struct error_code* codes ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* filename ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* hfn ; 
 char* id_str ; 
 char* name ; 
 int number ; 

__attribute__((used)) static int
generate_c(void)
{
    int n;
    struct error_code *ec;

    FILE *c_file = fopen(cfn, "w");
    if(c_file == NULL)
	return 1;

    fprintf(c_file, "/* Generated from %s */\n", filename);
    if(id_str)
	fprintf(c_file, "/* %s */\n", id_str);
    fprintf(c_file, "\n");
    fprintf(c_file, "#include <stddef.h>\n");
    fprintf(c_file, "#include <com_err.h>\n");
    fprintf(c_file, "#include \"%s\"\n", hfn);
    fprintf(c_file, "\n");
    fprintf(c_file, "#define N_(x) (x)\n");
    fprintf(c_file, "\n");

    fprintf(c_file, "static const char *%s_error_strings[] = {\n", name);

    for(ec = codes, n = 0; ec; ec = ec->next, n++) {
	while(n < ec->number) {
	    fprintf(c_file, "\t/* %03d */ \"Reserved %s error (%d)\",\n",
		    n, name, n);
	    n++;

	}
	fprintf(c_file, "\t/* %03d */ N_(\"%s\"),\n",
		ec->number, ec->string);
    }

    fprintf(c_file, "\tNULL\n");
    fprintf(c_file, "};\n");
    fprintf(c_file, "\n");
    fprintf(c_file, "#define num_errors %d\n", number);
    fprintf(c_file, "\n");
    fprintf(c_file,
	    "void initialize_%s_error_table_r(struct et_list **list)\n",
	    name);
    fprintf(c_file, "{\n");
    fprintf(c_file,
	    "    initialize_error_table_r(list, %s_error_strings, "
	    "num_errors, ERROR_TABLE_BASE_%s);\n", name, name);
    fprintf(c_file, "}\n");
    fprintf(c_file, "\n");
    fprintf(c_file, "void initialize_%s_error_table(void)\n", name);
    fprintf(c_file, "{\n");
    fprintf(c_file,
	    "    init_error_table(%s_error_strings, ERROR_TABLE_BASE_%s, "
	    "num_errors);\n", name, name);
    fprintf(c_file, "}\n");

    fclose(c_file);
    return 0;
}