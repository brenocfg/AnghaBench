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
struct error_code {char* name; int number; struct error_code* next; } ;
typedef  int /*<<< orphan*/  fn ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  base_id ; 
 struct error_code* codes ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* filename ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* hfn ; 
 char* id_str ; 
 int /*<<< orphan*/  isalnum (unsigned char) ; 
 char* name ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
generate_h(void)
{
    struct error_code *ec;
    char fn[128];
    FILE *h_file = fopen(hfn, "w");
    char *p;

    if(h_file == NULL)
	return 1;

    snprintf(fn, sizeof(fn), "__%s__", hfn);
    for(p = fn; *p; p++)
	if(!isalnum((unsigned char)*p))
	    *p = '_';

    fprintf(h_file, "/* Generated from %s */\n", filename);
    if(id_str)
	fprintf(h_file, "/* %s */\n", id_str);
    fprintf(h_file, "\n");
    fprintf(h_file, "#ifndef %s\n", fn);
    fprintf(h_file, "#define %s\n", fn);
    fprintf(h_file, "\n");
    fprintf(h_file, "struct et_list;\n");
    fprintf(h_file, "\n");
    fprintf(h_file,
	    "void initialize_%s_error_table_r(struct et_list **);\n",
	    name);
    fprintf(h_file, "\n");
    fprintf(h_file, "void initialize_%s_error_table(void);\n", name);
    fprintf(h_file, "#define init_%s_err_tbl initialize_%s_error_table\n",
	    name, name);
    fprintf(h_file, "\n");
    fprintf(h_file, "typedef enum %s_error_number{\n", name);

    for(ec = codes; ec; ec = ec->next) {
	fprintf(h_file, "\t%s = %ld%s\n", ec->name, base_id + ec->number,
		(ec->next != NULL) ? "," : "");
    }

    fprintf(h_file, "} %s_error_number;\n", name);
    fprintf(h_file, "\n");
    fprintf(h_file, "#define ERROR_TABLE_BASE_%s %ld\n", name, base_id);
    fprintf(h_file, "\n");
    fprintf(h_file, "#define COM_ERR_BINDDOMAIN_%s \"heim_com_err%ld\"\n", name, base_id);
    fprintf(h_file, "\n");
    fprintf(h_file, "#endif /* %s */\n", fn);


    fclose(h_file);
    return 0;
}