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
typedef  int /*<<< orphan*/  u_char ;
struct ng_parse_type {struct ng_parse_fixedstring_info* info; } ;
struct ng_parse_fixedstring_info {int bufSize; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_NETGRAPH_PARSE ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* ng_get_string_token (char const*,int*,int*,int*) ; 

__attribute__((used)) static int
ng_fixedstring_parse(const struct ng_parse_type *type,
	const char *s, int *off, const u_char *const start,
	u_char *const buf, int *buflen)
{
	const struct ng_parse_fixedstring_info *const fi = type->info;
	char *sval;
	int len;
	int slen;

	if ((sval = ng_get_string_token(s, off, &len, &slen)) == NULL)
		return (EINVAL);
	if (slen + 1 > fi->bufSize) {
		free(sval, M_NETGRAPH_PARSE);
		return (E2BIG);
	}
	*off += len;
	bcopy(sval, buf, slen);
	free(sval, M_NETGRAPH_PARSE);
	bzero(buf + slen, fi->bufSize - slen);
	*buflen = fi->bufSize;
	return (0);
}