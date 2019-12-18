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
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  ctype_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
 int /*<<< orphan*/  add_ctype_impl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errf (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * get_ctype (scalar_t__) ; 
 scalar_t__ last_ctype ; 

void
add_ctype_range(wchar_t end)
{
	ctype_node_t	*ctn;
	wchar_t		cur;

	if (end < last_ctype) {
		errf("malformed character range (%u ... %u))",
		    last_ctype, end);
		return;
	}
	for (cur = last_ctype + 1; cur <= end; cur++) {
		if ((ctn = get_ctype(cur)) == NULL) {
			INTERR;
			return;
		}
		add_ctype_impl(ctn);
	}
	last_ctype = end;

}