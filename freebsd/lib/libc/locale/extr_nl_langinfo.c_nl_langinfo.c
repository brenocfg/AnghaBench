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
typedef  int /*<<< orphan*/  nl_item ;

/* Variables and functions */
 int /*<<< orphan*/  __get_locale () ; 
 char* nl_langinfo_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
nl_langinfo(nl_item item)
{
	return nl_langinfo_l(item, __get_locale());
}