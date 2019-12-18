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
struct vector_str {int size; int /*<<< orphan*/ * container; } ;
struct vector_type_qualifier {struct vector_str ext_name; } ;
struct cpp_demangle_data {scalar_t__ push_head; int paren; int pfirst; char* cur; struct vector_str output_tmp; struct vector_str output; struct vector_str subst; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_CMX ; 
 int /*<<< orphan*/  TYPE_CST ; 
 int /*<<< orphan*/  TYPE_EXT ; 
 int /*<<< orphan*/  TYPE_IMG ; 
 int /*<<< orphan*/  TYPE_PTR ; 
 int /*<<< orphan*/  TYPE_REF ; 
 int /*<<< orphan*/  TYPE_RST ; 
 int /*<<< orphan*/  TYPE_VAT ; 
 int /*<<< orphan*/  TYPE_VEC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_demangle_push_str (struct cpp_demangle_data*,char*,int) ; 
 int /*<<< orphan*/  cpp_demangle_push_type_qualifier (struct cpp_demangle_data*,struct vector_type_qualifier*,char*) ; 
 int /*<<< orphan*/  cpp_demangle_read_array (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_expression_flat (struct cpp_demangle_data*,char**) ; 
 int /*<<< orphan*/  cpp_demangle_read_function (struct cpp_demangle_data*,int*,struct vector_type_qualifier*) ; 
 int /*<<< orphan*/  cpp_demangle_read_name (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_number (struct cpp_demangle_data*,long*) ; 
 int /*<<< orphan*/  cpp_demangle_read_number_as_string (struct cpp_demangle_data*,char**) ; 
 int /*<<< orphan*/  cpp_demangle_read_pointer_to_member (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_sname (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_subst (struct cpp_demangle_data*) ; 
 scalar_t__ cpp_demangle_read_tmpl_args (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_tmpl_param (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vector_str_dest (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_find (struct vector_str*,char*,size_t) ; 
 int /*<<< orphan*/  vector_str_init (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_pop (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_push (struct vector_str*,char*,int) ; 
 int /*<<< orphan*/  vector_str_push_vector_head (struct vector_str*,struct vector_str*) ; 
 char* vector_str_substr (struct vector_str*,size_t,int,size_t*) ; 
 int /*<<< orphan*/  vector_type_qualifier_dest (struct vector_type_qualifier*) ; 
 int /*<<< orphan*/  vector_type_qualifier_init (struct vector_type_qualifier*) ; 
 int /*<<< orphan*/  vector_type_qualifier_push (struct vector_type_qualifier*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpp_demangle_read_type(struct cpp_demangle_data *ddata, int delimit)
{
	struct vector_type_qualifier v;
	struct vector_str *output;
	size_t p_idx, type_str_len;
	int extern_c, is_builtin;
	long len;
	char *type_str, *exp_str, *num_str;

	if (ddata == NULL)
		return (0);

	output = &ddata->output;
	if (ddata->output.size > 0 && !strncmp(ddata->output.container[ddata->output.size - 1], ">", 1)) {
		ddata->push_head++;
		output = &ddata->output_tmp;
	} else if (delimit == 1) {
		if (ddata->paren == false) {
			if (!cpp_demangle_push_str(ddata, "(", 1))
				return (0);
			if (ddata->output.size < 2)
				return (0);
			ddata->paren = true;
			ddata->pfirst = true;
			/* Need pop function name */
			if (ddata->subst.size == 1 &&
			    !vector_str_pop(&ddata->subst))
				return (0);
		}

		if (ddata->pfirst)
			ddata->pfirst = false;
		else if (*ddata->cur != 'I' &&
		    !cpp_demangle_push_str(ddata, ", ", 2))
			return (0);
	}

	assert(output != NULL);
	/*
	 * [r, V, K] [P, R, C, G, U] builtin, function, class-enum, array
	 * pointer-to-member, template-param, template-template-param, subst
	 */

	if (!vector_type_qualifier_init(&v))
		return (0);

	extern_c = 0;
	is_builtin = 1;
	p_idx = output->size;
	type_str = exp_str = num_str = NULL;
again:
	/* builtin type */
	switch (*ddata->cur) {
	case 'a':
		/* signed char */
		if (!cpp_demangle_push_str(ddata, "signed char", 11))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'A':
		/* array type */
		if (!cpp_demangle_read_array(ddata))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 'b':
		/* bool */
		if (!cpp_demangle_push_str(ddata, "bool", 4))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'C':
		/* complex pair */
		if (!vector_type_qualifier_push(&v, TYPE_CMX))
			goto clean;
		++ddata->cur;
		goto again;

	case 'c':
		/* char */
		if (!cpp_demangle_push_str(ddata, "char", 4))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'd':
		/* double */
		if (!cpp_demangle_push_str(ddata, "double", 6))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'D':
		++ddata->cur;
		switch (*ddata->cur) {
		case 'd':
			/* IEEE 754r decimal floating point (64 bits) */
			if (!cpp_demangle_push_str(ddata, "decimal64", 9))
				goto clean;
			++ddata->cur;
			break;
		case 'e':
			/* IEEE 754r decimal floating point (128 bits) */
			if (!cpp_demangle_push_str(ddata, "decimal128", 10))
				goto clean;
			++ddata->cur;
			break;
		case 'f':
			/* IEEE 754r decimal floating point (32 bits) */
			if (!cpp_demangle_push_str(ddata, "decimal32", 9))
				goto clean;
			++ddata->cur;
			break;
		case 'h':
			/* IEEE 754r half-precision floating point (16 bits) */
			if (!cpp_demangle_push_str(ddata, "half", 4))
				goto clean;
			++ddata->cur;
			break;
		case 'i':
			/* char32_t */
			if (!cpp_demangle_push_str(ddata, "char32_t", 8))
				goto clean;
			++ddata->cur;
			break;
		case 'n':
			/* std::nullptr_t (i.e., decltype(nullptr)) */
			if (!cpp_demangle_push_str(ddata, "decltype(nullptr)",
			    17))
				goto clean;
			++ddata->cur;
			break;
		case 's':
			/* char16_t */
			if (!cpp_demangle_push_str(ddata, "char16_t", 8))
				goto clean;
			++ddata->cur;
			break;
		case 'v':
			/* gcc vector_size extension. */
			++ddata->cur;
			if (*ddata->cur == '_') {
				++ddata->cur;
				if (!cpp_demangle_read_expression_flat(ddata,
				    &exp_str))
					goto clean;
				if (!vector_str_push(&v.ext_name, exp_str,
				    strlen(exp_str)))
					goto clean;
			} else {
				if (!cpp_demangle_read_number_as_string(ddata,
				    &num_str))
					goto clean;
				if (!vector_str_push(&v.ext_name, num_str,
				    strlen(num_str)))
					goto clean;
			}
			if (*ddata->cur != '_')
				goto clean;
			++ddata->cur;
			if (!vector_type_qualifier_push(&v, TYPE_VEC))
				goto clean;
			goto again;
		default:
			goto clean;
		}
		goto rtn;

	case 'e':
		/* long double */
		if (!cpp_demangle_push_str(ddata, "long double", 11))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'f':
		/* float */
		if (!cpp_demangle_push_str(ddata, "float", 5))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'F':
		/* function */
		if (!cpp_demangle_read_function(ddata, &extern_c, &v))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 'g':
		/* __float128 */
		if (!cpp_demangle_push_str(ddata, "__float128", 10))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'G':
		/* imaginary */
		if (!vector_type_qualifier_push(&v, TYPE_IMG))
			goto clean;
		++ddata->cur;
		goto again;

	case 'h':
		/* unsigned char */
		if (!cpp_demangle_push_str(ddata, "unsigned char", 13))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'i':
		/* int */
		if (!cpp_demangle_push_str(ddata, "int", 3))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'j':
		/* unsigned int */
		if (!cpp_demangle_push_str(ddata, "unsigned int", 12))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'K':
		/* const */
		if (!vector_type_qualifier_push(&v, TYPE_CST))
			goto clean;
		++ddata->cur;
		goto again;

	case 'l':
		/* long */
		if (!cpp_demangle_push_str(ddata, "long", 4))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'm':
		/* unsigned long */
		if (!cpp_demangle_push_str(ddata, "unsigned long", 13))
			goto clean;

		++ddata->cur;

		goto rtn;
	case 'M':
		/* pointer to member */
		if (!cpp_demangle_read_pointer_to_member(ddata))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 'n':
		/* __int128 */
		if (!cpp_demangle_push_str(ddata, "__int128", 8))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'o':
		/* unsigned __int128 */
		if (!cpp_demangle_push_str(ddata, "unsigned __int128", 17))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'P':
		/* pointer */
		if (!vector_type_qualifier_push(&v, TYPE_PTR))
			goto clean;
		++ddata->cur;
		goto again;

	case 'r':
		/* restrict */
		if (!vector_type_qualifier_push(&v, TYPE_RST))
			goto clean;
		++ddata->cur;
		goto again;

	case 'R':
		/* reference */
		if (!vector_type_qualifier_push(&v, TYPE_REF))
			goto clean;
		++ddata->cur;
		goto again;

	case 's':
		/* short, local string */
		if (!cpp_demangle_push_str(ddata, "short", 5))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'S':
		/* substitution */
		if (!cpp_demangle_read_subst(ddata))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 't':
		/* unsigned short */
		if (!cpp_demangle_push_str(ddata, "unsigned short", 14))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'T':
		/* template parameter */
		if (!cpp_demangle_read_tmpl_param(ddata))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 'u':
		/* vendor extended builtin */
		++ddata->cur;
		if (!cpp_demangle_read_sname(ddata))
			goto clean;
		is_builtin = 0;
		goto rtn;

	case 'U':
		/* vendor extended type qualifier */
		if (!cpp_demangle_read_number(ddata, &len))
			goto clean;
		if (len <= 0)
			goto clean;
		if (!vector_str_push(&v.ext_name, ddata->cur, len))
			return (0);
		ddata->cur += len;
		if (!vector_type_qualifier_push(&v, TYPE_EXT))
			goto clean;
		goto again;

	case 'v':
		/* void */
		if (!cpp_demangle_push_str(ddata, "void", 4))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'V':
		/* volatile */
		if (!vector_type_qualifier_push(&v, TYPE_VAT))
			goto clean;
		++ddata->cur;
		goto again;

	case 'w':
		/* wchar_t */
		if (!cpp_demangle_push_str(ddata, "wchar_t", 7))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'x':
		/* long long */
		if (!cpp_demangle_push_str(ddata, "long long", 9))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'y':
		/* unsigned long long */
		if (!cpp_demangle_push_str(ddata, "unsigned long long", 18))
			goto clean;
		++ddata->cur;
		goto rtn;

	case 'z':
		/* ellipsis */
		if (!cpp_demangle_push_str(ddata, "...", 3))
			goto clean;
		++ddata->cur;
		goto rtn;
	}

	if (!cpp_demangle_read_name(ddata))
		goto clean;

	is_builtin = 0;
rtn:
	if ((type_str = vector_str_substr(output, p_idx, output->size - 1,
	    &type_str_len)) == NULL)
		goto clean;

	if (is_builtin == 0) {
		if (!vector_str_find(&ddata->subst, type_str, type_str_len) &&
		    !vector_str_push(&ddata->subst, type_str, type_str_len))
			goto clean;
	}

	if (!cpp_demangle_push_type_qualifier(ddata, &v, type_str))
		goto clean;

	free(type_str);
	free(exp_str);
	free(num_str);
	vector_type_qualifier_dest(&v);

	if (ddata->push_head > 0) {
		if (*ddata->cur == 'I' && cpp_demangle_read_tmpl_args(ddata)
		    == 0)
			return (0);

		if (--ddata->push_head > 0)
			return (1);

		if (!vector_str_push(&ddata->output_tmp, " ", 1))
			return (0);

		if (!vector_str_push_vector_head(&ddata->output,
		    &ddata->output_tmp))
			return (0);

		vector_str_dest(&ddata->output_tmp);
		if (!vector_str_init(&ddata->output_tmp))
			return (0);

		if (!cpp_demangle_push_str(ddata, "(", 1))
			return (0);

		ddata->paren = true;
		ddata->pfirst = true;
	}

	return (1);
clean:
	free(type_str);
	free(exp_str);
	free(num_str);
	vector_type_qualifier_dest(&v);

	return (0);
}