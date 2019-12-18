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
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct ng_parse_type {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NETGRAPH_PARSE ; 
 int /*<<< orphan*/  free (char* const,int /*<<< orphan*/ ) ; 
 char* ng_encode_string (char const* const,int const) ; 
 int ng_parse_append (char**,int*,char*,char* const) ; 

__attribute__((used)) static int
ng_sizedstring_unparse(const struct ng_parse_type *type,
	const u_char *data, int *off, char *cbuf, int cbuflen)
{
	const char *const raw = (const char *)data + *off + 2;
	const int slen = *((const u_int16_t *)(data + *off));
	char *const s = ng_encode_string(raw, slen);
	int error;

	if (s == NULL)
		return (ENOMEM);
	if ((error = ng_parse_append(&cbuf, &cbuflen, "%s", s)) != 0) {
		free(s, M_NETGRAPH_PARSE);
		return (error);
	}
	free(s, M_NETGRAPH_PARSE);
	*off += slen + 2;
	return (0);
}