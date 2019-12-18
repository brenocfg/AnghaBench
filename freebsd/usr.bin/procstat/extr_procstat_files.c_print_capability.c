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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_2__ {int /*<<< orphan*/  cd_desc; int /*<<< orphan*/  cd_right; } ;

/* Variables and functions */
 TYPE_1__* cap_desc ; 
 size_t cap_desc_count ; 
 scalar_t__ cap_rights_is_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 size_t width_capability (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

__attribute__((used)) static void
print_capability(cap_rights_t *rightsp, u_int capwidth)
{
	u_int count, i, width;

	count = 0;
	width = 0;
	for (i = width_capability(rightsp); i < capwidth; i++) {
		if (i != 0)
			xo_emit(" ");
		else
			xo_emit("-");
	}
	xo_open_list("capabilities");
	for (i = 0; i < cap_desc_count; i++) {
		if (cap_rights_is_set(rightsp, cap_desc[i].cd_right)) {
			xo_emit("{D:/%s}{l:capabilities/%s}", count ? "," : "",
			    cap_desc[i].cd_desc);
			width += strlen(cap_desc[i].cd_desc);
			if (count)
				width++;
			count++;
		}
	}
	xo_close_list("capabilities");
}