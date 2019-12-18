#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* str; TYPE_2__** child; } ;
struct TYPE_6__ {char* key; long n; TYPE_1__ v; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ kson_node_t ;

/* Variables and functions */
 int KSON_ERR_EXTRA_LEFT ; 
 int KSON_ERR_EXTRA_RIGHT ; 
 int KSON_ERR_NO_KEY ; 
 int KSON_OK ; 
 int /*<<< orphan*/  KSON_TYPE_BRACE ; 
 int /*<<< orphan*/  KSON_TYPE_BRACKET ; 
 int /*<<< orphan*/  KSON_TYPE_DBL_QUOTE ; 
 int /*<<< orphan*/  KSON_TYPE_NO_QUOTE ; 
 int /*<<< orphan*/  KSON_TYPE_SGL_QUOTE ; 
 int /*<<< orphan*/  __new_node (TYPE_2__**) ; 
 int /*<<< orphan*/  __push_back (long) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (long*) ; 
 scalar_t__ isspace (char const) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

kson_node_t *kson_parse_core(const char *json, long *_n, int *error, long *parsed_len)
{
	long *stack = 0, top = 0, max = 0, n_a = 0, m_a = 0, i, j;
	kson_node_t *a = 0, *u;
	const char *p, *q;
	size_t *tmp;

#define __push_back(y) do { \
		if (top == max) { \
			max = max? max<<1 : 4; \
			stack = (long*)realloc(stack, sizeof(long) * max); \
		} \
		stack[top++] = (y); \
	} while (0)

#define __new_node(z) do { \
		if (n_a == m_a) { \
			long old_m = m_a; \
			m_a = m_a? m_a<<1 : 4; \
			a = (kson_node_t*)realloc(a, sizeof(kson_node_t) * m_a); \
			memset(a + old_m, 0, sizeof(kson_node_t) * (m_a - old_m)); \
		} \
		*(z) = &a[n_a++]; \
	} while (0)

	assert(sizeof(size_t) == sizeof(kson_node_t*));
	*error = KSON_OK;
	for (p = json; *p; ++p) {
		while (*p && isspace(*p)) ++p;
		if (*p == 0) break;
		if (*p == ',') { // comma is somewhat redundant
		} else if (*p == '[' || *p == '{') {
			int t = *p == '['? -1 : -2;
			if (top < 2 || stack[top-1] != -3) { // unnamed internal node
				__push_back(n_a);
				__new_node(&u);
				__push_back(t);
			} else stack[top-1] = t; // named internal node
		} else if (*p == ']' || *p == '}') {
			long i, start, t = *p == ']'? -1 : -2;
			for (i = top - 1; i >= 0 && stack[i] != t; --i);
			if (i < 0) { // error: an extra right bracket
				*error = KSON_ERR_EXTRA_RIGHT;
				break;
			}
			start = i;
			u = &a[stack[start-1]];
			u->key = u->v.str;
			u->n = top - 1 - start;
			u->v.child = (kson_node_t**)malloc(u->n * sizeof(kson_node_t*));
			tmp = (size_t*)u->v.child;
			for (i = start + 1; i < top; ++i)
				tmp[i - start - 1] = stack[i];
			u->type = *p == ']'? KSON_TYPE_BRACKET : KSON_TYPE_BRACE;
			if ((top = start) == 1) break; // completed one object; remaining characters discarded
		} else if (*p == ':') {
			if (top == 0 || stack[top-1] == -3) {
				*error = KSON_ERR_NO_KEY;
				break;
			}
			__push_back(-3);
		} else {
			int c = *p;
			// get the node to modify
			if (top >= 2 && stack[top-1] == -3) { // we have a key:value pair here
				--top;
				u = &a[stack[top-1]];
				u->key = u->v.str; // move old value to key
			} else { // don't know if this is a bare value or a key:value pair; keep it as a value for now
				__push_back(n_a);
				__new_node(&u);
			}
			// parse string
			if (c == '\'' || c == '"') {
				for (q = ++p; *q && *q != c; ++q)
					if (*q == '\\') ++q;
			} else {
				for (q = p; *q && *q != ']' && *q != '}' && *q != ',' && *q != ':' && *q != '\n'; ++q)
					if (*q == '\\') ++q;
			}
			u->v.str = (char*)malloc(q - p + 1); strncpy(u->v.str, p, q - p); u->v.str[q-p] = 0; // equivalent to u->v.str=strndup(p, q-p)
			u->type = c == '\''? KSON_TYPE_SGL_QUOTE : c == '"'? KSON_TYPE_DBL_QUOTE : KSON_TYPE_NO_QUOTE;
			p = c == '\'' || c == '"'? q : q - 1;
		}
	}
	while (*p && isspace(*p)) ++p; // skip trailing blanks
	if (parsed_len) *parsed_len = p - json;
	if (top != 1) *error = KSON_ERR_EXTRA_LEFT;

	for (i = 0; i < n_a; ++i)
		for (j = 0, u = &a[i], tmp = (size_t*)u->v.child; j < (long)u->n; ++j)
			u->v.child[j] = &a[tmp[j]];

	free(stack);
	*_n = n_a;
	return a;
}