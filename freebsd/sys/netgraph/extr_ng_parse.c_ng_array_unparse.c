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
 int /*<<< orphan*/  CT_ARRAY ; 
 int ng_unparse_composite (struct ng_parse_type const*,int /*<<< orphan*/  const*,int*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_array_unparse(const struct ng_parse_type *type,
	const u_char *data, int *off, char *cbuf, int cbuflen)
{
	return ng_unparse_composite(type, data, off, cbuf, cbuflen, CT_ARRAY);
}