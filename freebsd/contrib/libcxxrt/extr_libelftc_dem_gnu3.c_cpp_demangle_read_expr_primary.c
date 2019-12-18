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
struct cpp_demangle_data {char* cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELFTC_ISDIGIT (char) ; 
 int cpp_demangle_push_fp (struct cpp_demangle_data*,int /*<<< orphan*/ ) ; 
 int cpp_demangle_push_str (struct cpp_demangle_data*,char const*,int) ; 
 int /*<<< orphan*/  cpp_demangle_read_encoding (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  decode_fp_to_double ; 
 int /*<<< orphan*/  decode_fp_to_float ; 
 int /*<<< orphan*/  decode_fp_to_float128 ; 
 int /*<<< orphan*/  decode_fp_to_float80 ; 

__attribute__((used)) static int
cpp_demangle_read_expr_primary(struct cpp_demangle_data *ddata)
{
	const char *num;

	if (ddata == NULL || *(++ddata->cur) == '\0')
		return (0);

	if (*ddata->cur == '_' && *(ddata->cur + 1) == 'Z') {
		ddata->cur += 2;
		if (*ddata->cur == '\0')
			return (0);
		if (!cpp_demangle_read_encoding(ddata))
			return (0);
		++ddata->cur;
		return (1);
	}

	switch (*ddata->cur) {
	case 'b':
		if (*(ddata->cur + 2) != 'E')
			return (0);
		switch (*(++ddata->cur)) {
		case '0':
			ddata->cur += 2;
			return (cpp_demangle_push_str(ddata, "false", 5));
		case '1':
			ddata->cur += 2;
			return (cpp_demangle_push_str(ddata, "true", 4));
		default:
			return (0);
		}

	case 'd':
		++ddata->cur;
		return (cpp_demangle_push_fp(ddata, decode_fp_to_double));

	case 'e':
		++ddata->cur;
		if (sizeof(long double) == 10)
			return (cpp_demangle_push_fp(ddata,
			    decode_fp_to_double));
		return (cpp_demangle_push_fp(ddata, decode_fp_to_float80));

	case 'f':
		++ddata->cur;
		return (cpp_demangle_push_fp(ddata, decode_fp_to_float));

	case 'g':
		++ddata->cur;
		if (sizeof(long double) == 16)
			return (cpp_demangle_push_fp(ddata,
			    decode_fp_to_double));
		return (cpp_demangle_push_fp(ddata, decode_fp_to_float128));

	case 'i':
	case 'j':
	case 'l':
	case 'm':
	case 'n':
	case 's':
	case 't':
	case 'x':
	case 'y':
		if (*(++ddata->cur) == 'n') {
			if (!cpp_demangle_push_str(ddata, "-", 1))
				return (0);
			++ddata->cur;
		}
		num = ddata->cur;
		while (*ddata->cur != 'E') {
			if (!ELFTC_ISDIGIT(*ddata->cur))
				return (0);
			++ddata->cur;
		}
		++ddata->cur;
		return (cpp_demangle_push_str(ddata, num,
		    ddata->cur - num - 1));

	default:
		return (0);
	}
}