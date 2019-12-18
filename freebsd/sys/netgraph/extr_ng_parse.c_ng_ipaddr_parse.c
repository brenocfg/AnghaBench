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
struct ng_parse_type {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ng_int8_parse (int /*<<< orphan*/ *,char const*,int*,int /*<<< orphan*/  const* const,int /*<<< orphan*/ * const,int*) ; 
 int /*<<< orphan*/  ng_parse_int8_type ; 

__attribute__((used)) static int
ng_ipaddr_parse(const struct ng_parse_type *type,
	const char *s, int *off, const u_char *const start,
	u_char *const buf, int *buflen)
{
	int i, error;

	for (i = 0; i < 4; i++) {
		if ((error = ng_int8_parse(&ng_parse_int8_type,
		    s, off, start, buf + i, buflen)) != 0)
			return (error);
		if (i < 3 && s[*off] != '.')
			return (EINVAL);
		(*off)++;
	}
	*buflen = 4;
	return (0);
}