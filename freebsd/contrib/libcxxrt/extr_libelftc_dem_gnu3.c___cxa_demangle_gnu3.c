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
struct TYPE_3__ {scalar_t__ size; } ;
struct cpp_demangle_data {char* cur; TYPE_1__ output; scalar_t__ mem_rst; scalar_t__ mem_cst; scalar_t__ mem_vat; scalar_t__ paren; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DEMANGLE_TRY_LIMIT ; 
 int /*<<< orphan*/  cpp_demangle_data_dest (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_data_init (struct cpp_demangle_data*,char const*) ; 
 int /*<<< orphan*/  cpp_demangle_read_encoding (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_type (struct cpp_demangle_data*,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char* vector_str_get_flat (TYPE_1__*,size_t*) ; 
 int /*<<< orphan*/  vector_str_push (TYPE_1__*,char*,int) ; 

char *
__cxa_demangle_gnu3(const char *org)
{
	struct cpp_demangle_data ddata;
	ssize_t org_len;
	unsigned int limit;
	char *rtn = NULL;

	if (org == NULL)
		return (NULL);

	org_len = strlen(org);
	if (org_len > 11 && !strncmp(org, "_GLOBAL__I_", 11)) {
		if ((rtn = malloc(org_len + 19)) == NULL)
			return (NULL);
		snprintf(rtn, org_len + 19,
		    "global constructors keyed to %s", org + 11);
		return (rtn);
	}

	// Try demangling as a type for short encodings
	if ((org_len < 2) || (org[0] != '_' || org[1] != 'Z' )) {
		if (!cpp_demangle_data_init(&ddata, org))
			return (NULL);
		if (!cpp_demangle_read_type(&ddata, 0))
			goto clean;
		rtn = vector_str_get_flat(&ddata.output, (size_t *) NULL);
		goto clean;
	}


	if (!cpp_demangle_data_init(&ddata, org + 2))
		return (NULL);

	rtn = NULL;

	if (!cpp_demangle_read_encoding(&ddata))
		goto clean;

	limit = 0;
	while (*ddata.cur != '\0') {
		/*
		 * Breaking at some gcc info at tail. e.g) @@GLIBCXX_3.4
		 */
		if (*ddata.cur == '@' && *(ddata.cur + 1) == '@')
			break;
		if (!cpp_demangle_read_type(&ddata, 1))
			goto clean;
		if (limit++ > CPP_DEMANGLE_TRY_LIMIT)
			goto clean;
	}

	if (ddata.output.size == 0)
		goto clean;
	if (ddata.paren && !vector_str_push(&ddata.output, ")", 1))
		goto clean;
	if (ddata.mem_vat && !vector_str_push(&ddata.output, " volatile", 9))
		goto clean;
	if (ddata.mem_cst && !vector_str_push(&ddata.output, " const", 6))
		goto clean;
	if (ddata.mem_rst && !vector_str_push(&ddata.output, " restrict", 9))
		goto clean;

	rtn = vector_str_get_flat(&ddata.output, (size_t *) NULL);

clean:
	cpp_demangle_data_dest(&ddata);

	return (rtn);
}