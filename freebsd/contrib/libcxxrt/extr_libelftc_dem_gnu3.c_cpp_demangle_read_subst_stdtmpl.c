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
struct vector_str {size_t size; } ;
struct cpp_demangle_data {scalar_t__ push_head; struct vector_str output; struct vector_str output_tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpp_demangle_push_subst (struct cpp_demangle_data*,char*,size_t) ; 
 int /*<<< orphan*/  cpp_demangle_read_tmpl_args (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* vector_str_substr (struct vector_str*,size_t,int,size_t*) ; 

__attribute__((used)) static int
cpp_demangle_read_subst_stdtmpl(struct cpp_demangle_data *ddata,
    const char *str, size_t len)
{
	struct vector_str *output;
	size_t p_idx, substr_len;
	int rtn;
	char *subst_str, *substr;

	if (ddata == NULL || str == NULL || len == 0)
		return (0);

	output = ddata->push_head > 0 ? &ddata->output_tmp : &ddata->output;

	p_idx = output->size;
	substr = NULL;
	subst_str = NULL;

	if (!cpp_demangle_read_tmpl_args(ddata))
		return (0);
	if ((substr = vector_str_substr(output, p_idx, output->size - 1,
	    &substr_len)) == NULL)
		return (0);

	rtn = 0;
	if ((subst_str = malloc(sizeof(char) * (substr_len + len + 1))) ==
	    NULL)
		goto clean;

	memcpy(subst_str, str, len);
	memcpy(subst_str + len, substr, substr_len);
	subst_str[substr_len + len] = '\0';

	if (!cpp_demangle_push_subst(ddata, subst_str, substr_len + len))
		goto clean;

	rtn = 1;
clean:
	free(subst_str);
	free(substr);

	return (rtn);
}