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

/* Variables and functions */
 int SIZE (char const* const*) ; 

char const *
hci_link2str(int link_type)
{
	static char const * const	t[] = {
		/* NG_HCI_LINK_SCO */ "SCO",
		/* NG_HCI_LINK_ACL */ "ACL"
	};

	return (link_type >= SIZE(t)? "?" : t[link_type]);
}