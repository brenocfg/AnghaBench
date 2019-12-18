#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const** container; int /*<<< orphan*/  size; } ;
struct vector_type_qualifier {size_t size; int* q_container; TYPE_1__ ext_name; } ;
struct vector_str {int dummy; } ;
struct cpp_demangle_data {int dummy; } ;

/* Variables and functions */
#define  TYPE_CMX 136 
#define  TYPE_CST 135 
#define  TYPE_EXT 134 
#define  TYPE_IMG 133 
#define  TYPE_PTR 132 
#define  TYPE_REF 131 
#define  TYPE_RST 130 
#define  TYPE_VAT 129 
#define  TYPE_VEC 128 
 int /*<<< orphan*/  cpp_demangle_push_str (struct cpp_demangle_data*,char*,size_t) ; 
 int /*<<< orphan*/  cpp_demangle_push_subst_v (struct cpp_demangle_data*,struct vector_str*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  vector_str_dest (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_init (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_push (struct vector_str*,char const*,size_t) ; 

__attribute__((used)) static int
cpp_demangle_push_type_qualifier(struct cpp_demangle_data *ddata,
    struct vector_type_qualifier *v, const char *type_str)
{
	struct vector_str subst_v;
	size_t idx, e_idx, e_len;
	int rtn;
	char *buf;

	if (ddata == NULL || v == NULL)
		return (0);

	if ((idx = v->size) == 0)
		return (1);

	rtn = 0;
	if (type_str != NULL) {
		if (!vector_str_init(&subst_v))
			return (0);
		if (!vector_str_push(&subst_v, type_str, strlen(type_str)))
			goto clean;
	}

	e_idx = 0;
	while (idx > 0) {
		switch (v->q_container[idx - 1]) {
		case TYPE_PTR:
			if (!cpp_demangle_push_str(ddata, "*", 1))
				goto clean;
			if (type_str != NULL) {
				if (!vector_str_push(&subst_v, "*", 1))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_REF:
			if (!cpp_demangle_push_str(ddata, "&", 1))
				goto clean;
			if (type_str != NULL) {
				if (!vector_str_push(&subst_v, "&", 1))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_CMX:
			if (!cpp_demangle_push_str(ddata, " complex", 8))
				goto clean;
			if (type_str != NULL) {
				if (!vector_str_push(&subst_v, " complex", 8))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_IMG:
			if (!cpp_demangle_push_str(ddata, " imaginary", 10))
				goto clean;
			if (type_str != NULL) {
				if (!vector_str_push(&subst_v, " imaginary",
				    10))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_EXT:
			if (v->ext_name.size == 0 ||
			    e_idx > v->ext_name.size - 1)
				goto clean;
			if ((e_len = strlen(v->ext_name.container[e_idx])) ==
			    0)
				goto clean;
			if ((buf = malloc(e_len + 2)) == NULL)
				goto clean;
			snprintf(buf, e_len + 2, " %s",
			    v->ext_name.container[e_idx]);

			if (!cpp_demangle_push_str(ddata, buf, e_len + 1)) {
				free(buf);
				goto clean;
			}

			if (type_str != NULL) {
				if (!vector_str_push(&subst_v, buf,
				    e_len + 1)) {
					free(buf);
					goto clean;
				}
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v)) {
					free(buf);
					goto clean;
				}
			}
			free(buf);
			++e_idx;
			break;

		case TYPE_RST:
			if (!cpp_demangle_push_str(ddata, " restrict", 9))
				goto clean;
			if (type_str != NULL) {
				if (!vector_str_push(&subst_v, " restrict", 9))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_VAT:
			if (!cpp_demangle_push_str(ddata, " volatile", 9))
				goto clean;
			if (type_str != NULL) {
				if (!vector_str_push(&subst_v, " volatile", 9))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_CST:
			if (!cpp_demangle_push_str(ddata, " const", 6))
				goto clean;
			if (type_str != NULL) {
				if (!vector_str_push(&subst_v, " const", 6))
					goto clean;
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v))
					goto clean;
			}
			break;

		case TYPE_VEC:
			if (v->ext_name.size == 0 ||
			    e_idx > v->ext_name.size - 1)
				goto clean;
			if ((e_len = strlen(v->ext_name.container[e_idx])) ==
			    0)
				goto clean;
			if ((buf = malloc(e_len + 12)) == NULL)
				goto clean;
			snprintf(buf, e_len + 12, " __vector(%s)",
			    v->ext_name.container[e_idx]);
			if (!cpp_demangle_push_str(ddata, buf, e_len + 11)) {
				free(buf);
				goto clean;
			}
			if (type_str != NULL) {
				if (!vector_str_push(&subst_v, buf,
				    e_len + 11)) {
					free(buf);
					goto clean;
				}
				if (!cpp_demangle_push_subst_v(ddata,
				    &subst_v)) {
					free(buf);
					goto clean;
				}
			}
			free(buf);
			++e_idx;
			break;
		}
		--idx;
	}

	rtn = 1;
clean:
	if (type_str != NULL)
		vector_str_dest(&subst_v);

	return (rtn);
}