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
struct vector_str {size_t size; int /*<<< orphan*/ * container; } ;
struct cpp_demangle_data {char* cur; scalar_t__ push_head; int /*<<< orphan*/  cmd; int /*<<< orphan*/  tmpl; struct vector_str output; struct vector_str output_tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DEMANGLE_TRY_LIMIT ; 
 int /*<<< orphan*/  READ_TMPL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cpp_demangle_push_str (struct cpp_demangle_data*,char*,int) ; 
 int /*<<< orphan*/  cpp_demangle_read_tmpl_arg (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int vector_read_cmd_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vector_read_cmd_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_str_find (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  vector_str_push (int /*<<< orphan*/ *,char*,size_t) ; 
 char* vector_str_substr (struct vector_str*,size_t,int,size_t*) ; 

__attribute__((used)) static int
cpp_demangle_read_tmpl_args(struct cpp_demangle_data *ddata)
{
	struct vector_str *v;
	size_t arg_len, idx, limit, size;
	char *arg;

	if (ddata == NULL || *ddata->cur == '\0')
		return (0);

	++ddata->cur;

	if (!vector_read_cmd_push(&ddata->cmd, READ_TMPL))
		return (0);

	if (!cpp_demangle_push_str(ddata, "<", 1))
		return (0);

	limit = 0;
	v = ddata->push_head > 0 ? &ddata->output_tmp : &ddata->output;
	for (;;) {
		idx = v->size;
		if (!cpp_demangle_read_tmpl_arg(ddata))
			return (0);
		if ((arg = vector_str_substr(v, idx, v->size - 1, &arg_len)) ==
		    NULL)
			return (0);
		if (!vector_str_find(&ddata->tmpl, arg, arg_len) &&
		    !vector_str_push(&ddata->tmpl, arg, arg_len)) {
			free(arg);
			return (0);
		}

		free(arg);

		if (*ddata->cur == 'E') {
			++ddata->cur;
			size = v->size;
			assert(size > 0);
			if (!strncmp(v->container[size - 1], ">", 1)) {
				if (!cpp_demangle_push_str(ddata, " >", 2))
					return (0);
			} else if (!cpp_demangle_push_str(ddata, ">", 1))
				return (0);
			break;
		} else if (*ddata->cur != 'I' &&
		    !cpp_demangle_push_str(ddata, ", ", 2))
			return (0);

		if (limit++ > CPP_DEMANGLE_TRY_LIMIT)
			return (0);
	}

	return (vector_read_cmd_pop(&ddata->cmd));
}