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
struct ifmedia_type_to_subtype {TYPE_1__* subtypes; } ;
struct ifmedia_description {int ifmt_word; int /*<<< orphan*/ * ifmt_string; } ;
struct TYPE_2__ {int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,...) ; 
 struct ifmedia_description* ifm_type_descriptions ; 
 struct ifmedia_type_to_subtype* ifmedia_types_to_subtypes ; 
 int lookup_media_word (int /*<<< orphan*/ *,char const*) ; 

int
get_media_subtype(int type, const char *val)
{
	struct ifmedia_description *desc;
	struct ifmedia_type_to_subtype *ttos;
	int rval, i;

	/* Find the top-level interface type. */
	for (desc = ifm_type_descriptions, ttos = ifmedia_types_to_subtypes;
	    desc->ifmt_string != NULL; desc++, ttos++)
		if (type == desc->ifmt_word)
			break;
	if (desc->ifmt_string == NULL)
		errx(1, "unknown media type 0x%x", type);

	for (i = 0; ttos->subtypes[i].desc != NULL; i++) {
		rval = lookup_media_word(ttos->subtypes[i].desc, val);
		if (rval != -1)
			return (rval);
	}
	errx(1, "unknown media subtype: %s", val);
	/*NOTREACHED*/
}