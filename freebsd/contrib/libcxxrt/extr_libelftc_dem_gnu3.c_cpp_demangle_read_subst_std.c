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
struct cpp_demangle_data {char* cur; scalar_t__ push_head; struct vector_str output; struct vector_str output_tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpp_demangle_push_str (struct cpp_demangle_data*,char*,int) ; 
 int /*<<< orphan*/  cpp_demangle_push_subst_v (struct cpp_demangle_data*,struct vector_str*) ; 
 int /*<<< orphan*/  cpp_demangle_read_tmpl_args (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_uqname (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  vector_str_dest (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_init (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_push (struct vector_str*,char*,size_t) ; 
 char* vector_str_substr (struct vector_str*,size_t,int,size_t*) ; 

__attribute__((used)) static int
cpp_demangle_read_subst_std(struct cpp_demangle_data *ddata)
{
	struct vector_str *output, v;
	size_t p_idx, subst_str_len;
	int rtn;
	char *subst_str;

	if (ddata == NULL)
		return (0);

	if (!vector_str_init(&v))
		return (0);

	subst_str = NULL;
	rtn = 0;
	if (!cpp_demangle_push_str(ddata, "std::", 5))
		goto clean;

	if (!vector_str_push(&v, "std::", 5))
		goto clean;

	ddata->cur += 2;

	output = ddata->push_head > 0 ? &ddata->output_tmp : &ddata->output;

	p_idx = output->size;
	if (!cpp_demangle_read_uqname(ddata))
		goto clean;

	if ((subst_str = vector_str_substr(output, p_idx, output->size - 1,
	    &subst_str_len)) == NULL)
		goto clean;

	if (!vector_str_push(&v, subst_str, subst_str_len))
		goto clean;

	if (!cpp_demangle_push_subst_v(ddata, &v))
		goto clean;

	if (*ddata->cur == 'I') {
		p_idx = output->size;
		if (!cpp_demangle_read_tmpl_args(ddata))
			goto clean;
		free(subst_str);
		if ((subst_str = vector_str_substr(output, p_idx,
		    output->size - 1, &subst_str_len)) == NULL)
			goto clean;
		if (!vector_str_push(&v, subst_str, subst_str_len))
			goto clean;
		if (!cpp_demangle_push_subst_v(ddata, &v))
			goto clean;
	}

	rtn = 1;
clean:
	free(subst_str);
	vector_str_dest(&v);

	return (rtn);
}