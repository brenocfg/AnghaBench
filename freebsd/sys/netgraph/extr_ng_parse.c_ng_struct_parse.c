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
 int /*<<< orphan*/  CT_STRUCT ; 
 int ng_parse_composite (struct ng_parse_type const*,char const*,int*,int /*<<< orphan*/  const* const,int /*<<< orphan*/ * const,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_struct_parse(const struct ng_parse_type *type,
	const char *s, int *off, const u_char *const start,
	u_char *const buf, int *buflen)
{
	return ng_parse_composite(type, s, off, start, buf, buflen, CT_STRUCT);
}