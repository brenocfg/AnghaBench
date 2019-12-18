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
typedef  int uint32_t ;
struct tok {int dummy; } ;

/* Variables and functions */
 struct tok* onf_exp_str ; 
 struct tok* oui_values ; 
 char const* tok2str (struct tok const*,char*,int const) ; 

const char *
of_vendor_name(const uint32_t vendor)
{
	const struct tok *table = (vendor & 0xff000000) == 0 ? oui_values : onf_exp_str;
	return tok2str(table, "unknown", vendor);
}