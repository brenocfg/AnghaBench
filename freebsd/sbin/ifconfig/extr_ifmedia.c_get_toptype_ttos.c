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
struct ifmedia_type_to_subtype {int dummy; } ;
struct ifmedia_description {scalar_t__ ifmt_word; int /*<<< orphan*/ * ifmt_string; } ;

/* Variables and functions */
 scalar_t__ IFM_TYPE (int) ; 
 struct ifmedia_description* ifm_type_descriptions ; 
 struct ifmedia_type_to_subtype* ifmedia_types_to_subtypes ; 

__attribute__((used)) static struct ifmedia_type_to_subtype *get_toptype_ttos(int ifmw)
{
	struct ifmedia_description *desc;
	struct ifmedia_type_to_subtype *ttos;

	for (desc = ifm_type_descriptions, ttos = ifmedia_types_to_subtypes;
	    desc->ifmt_string != NULL; desc++, ttos++)
		if (IFM_TYPE(ifmw) == desc->ifmt_word)
			break;

	return ttos;
}