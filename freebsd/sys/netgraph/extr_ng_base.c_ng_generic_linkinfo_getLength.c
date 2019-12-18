#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct ng_parse_type {int dummy; } ;
struct TYPE_2__ {int hooks; } ;
struct hooklist {TYPE_1__ nodeinfo; } ;

/* Variables and functions */

__attribute__((used)) static int
ng_generic_linkinfo_getLength(const struct ng_parse_type *type,
	const u_char *start, const u_char *buf)
{
	const struct hooklist *hl = (const struct hooklist *)start;

	return hl->nodeinfo.hooks;
}