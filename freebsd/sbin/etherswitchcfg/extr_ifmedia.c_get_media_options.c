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
struct ifmedia_type_to_subtype {TYPE_1__* options; } ;
struct ifmedia_description {int ifmt_word; int /*<<< orphan*/ * ifmt_string; } ;
struct TYPE_2__ {int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct ifmedia_description* ifm_type_descriptions ; 
 struct ifmedia_type_to_subtype* ifmedia_types_to_subtypes ; 
 int lookup_media_word (int /*<<< orphan*/ *,char*) ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 

int
get_media_options(int type, const char *val)
{
	struct ifmedia_description *desc;
	struct ifmedia_type_to_subtype *ttos;
	char *optlist, *optptr;
	int option = 0, i, rval = 0;

	/* We muck with the string, so copy it. */
	optlist = strdup(val);
	if (optlist == NULL)
		err(1, "strdup");

	/* Find the top-level interface type. */
	for (desc = ifm_type_descriptions, ttos = ifmedia_types_to_subtypes;
	    desc->ifmt_string != NULL; desc++, ttos++)
		if (type == desc->ifmt_word)
			break;
	if (desc->ifmt_string == NULL)
		errx(1, "unknown media type 0x%x", type);

	/*
	 * Look up the options in the user-provided comma-separated
	 * list.
	 */
	optptr = optlist;
	for (; (optptr = strtok(optptr, ",")) != NULL; optptr = NULL) {
		for (i = 0; ttos->options[i].desc != NULL; i++) {
			option = lookup_media_word(ttos->options[i].desc, optptr);
			if (option != -1)
				break;
		}
		if (option == 0)
			errx(1, "unknown option: %s", optptr);
		rval |= option;
	}

	free(optlist);
	return (rval);
}