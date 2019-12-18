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
typedef  int /*<<< orphan*/  quad_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bcopy (scalar_t__*,int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  strtoq (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_int64_parse(const struct ng_parse_type *type,
	const char *s, int *off, const u_char *const start,
	u_char *const buf, int *buflen)
{
	quad_t val;
	int64_t val64;
	char *eptr;

	val = strtoq(s + *off, &eptr, 0);
	if (eptr == s + *off)
		return (EINVAL);
	*off = eptr - s;
	val64 = (int64_t)val;
	bcopy(&val64, buf, sizeof(int64_t));
	*buflen = sizeof(int64_t);
	return (0);
}