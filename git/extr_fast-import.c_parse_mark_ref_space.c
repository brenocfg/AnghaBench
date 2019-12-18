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
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 TYPE_1__ command_buf ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_mark_ref (char const*,char**) ; 

__attribute__((used)) static uintmax_t parse_mark_ref_space(const char **p)
{
	uintmax_t mark;
	char *end;

	mark = parse_mark_ref(*p, &end);
	if (*end++ != ' ')
		die("Missing space after mark: %s", command_buf.buf);
	*p = end;
	return mark;
}