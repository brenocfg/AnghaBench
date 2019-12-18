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
struct ifmedia_description {char const* ifmt_string; } ;

/* Variables and functions */
 struct ifmedia_description* get_toptype_desc (int) ; 

const char *
ifconfig_media_get_type(int ifmw)
{
	struct ifmedia_description *desc;

	/*int seen_option = 0, i;*/

	/* Find the top-level interface type. */
	desc = get_toptype_desc(ifmw);
	if (desc->ifmt_string == NULL) {
		return ("<unknown type>");
	} else {
		return (desc->ifmt_string);
	}
}