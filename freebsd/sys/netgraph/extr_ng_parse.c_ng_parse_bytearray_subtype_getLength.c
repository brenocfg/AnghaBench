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
struct ng_parse_type {int (* private ) (struct ng_parse_type const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;} ;
typedef  int (* ng_parse_array_getLength_t ) (struct ng_parse_type const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;

/* Variables and functions */
 int stub1 (struct ng_parse_type const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
ng_parse_bytearray_subtype_getLength(const struct ng_parse_type *type,
	const u_char *start, const u_char *buf)
{
	ng_parse_array_getLength_t *const getLength = type->private;

	return (*getLength)(type, start, buf);
}