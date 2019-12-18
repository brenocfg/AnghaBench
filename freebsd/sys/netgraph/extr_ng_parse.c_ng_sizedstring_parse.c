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
typedef  scalar_t__ u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct ng_parse_type {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_NETGRAPH_PARSE ; 
 int USHRT_MAX ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* ng_get_string_token (char const*,int*,int*,int*) ; 

__attribute__((used)) static int
ng_sizedstring_parse(const struct ng_parse_type *type,
	const char *s, int *off, const u_char *const start,
	u_char *const buf, int *buflen)
{
	char *sval;
	int len;
	int slen;

	if ((sval = ng_get_string_token(s, off, &len, &slen)) == NULL)
		return (EINVAL);
	if (slen > USHRT_MAX) {
		free(sval, M_NETGRAPH_PARSE);
		return (EINVAL);
	}
	*off += len;
	*((u_int16_t *)buf) = (u_int16_t)slen;
	bcopy(sval, buf + 2, slen);
	free(sval, M_NETGRAPH_PARSE);
	*buflen = 2 + slen;
	return (0);
}