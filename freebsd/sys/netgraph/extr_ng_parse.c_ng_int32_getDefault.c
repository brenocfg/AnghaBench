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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  bcopy (scalar_t__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ng_int32_getDefault(const struct ng_parse_type *type,
	const u_char *const start, u_char *buf, int *buflen)
{
	int32_t val;

	if (*buflen < sizeof(int32_t))
		return (ERANGE);
	val = 0;
	bcopy(&val, buf, sizeof(int32_t));
	*buflen = sizeof(int32_t);
	return (0);
}