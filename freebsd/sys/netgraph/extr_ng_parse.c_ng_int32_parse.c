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
typedef  long u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct ng_parse_type {scalar_t__ info; } ;
typedef  long int32_t ;

/* Variables and functions */
 int EINVAL ; 
 intptr_t INT_SIGNED ; 
 int /*<<< orphan*/  bcopy (long*,int /*<<< orphan*/ * const,int) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_int32_parse(const struct ng_parse_type *type,
	const char *s, int *off, const u_char *const start,
	u_char *const buf, int *buflen)
{
	long val;			/* assumes long is at least 32 bits */
	int32_t val32;
	char *eptr;

	if ((intptr_t)type->info == INT_SIGNED)
		val = strtol(s + *off, &eptr, 0);
	else
		val = strtoul(s + *off, &eptr, 0);
	if (val < (int32_t)0x80000000
	    || val > (u_int32_t)0xffffffff || eptr == s + *off)
		return (EINVAL);
	*off = eptr - s;
	val32 = (int32_t)val;
	bcopy(&val32, buf, sizeof(int32_t));
	*buflen = sizeof(int32_t);
	return (0);
}