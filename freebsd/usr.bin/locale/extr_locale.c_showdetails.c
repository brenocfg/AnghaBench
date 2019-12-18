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
#define  TYPE_NUM 130 
#define  TYPE_STR 129 
#define  TYPE_UNQ 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kwval_lookup (char const*,char**,int*,int*,int*) ; 
 char* lookup_localecat (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ prt_categories ; 
 scalar_t__ prt_keywords ; 
 int /*<<< orphan*/  stderr ; 

void
showdetails(const char *kw)
{
	int	type, cat, tmpval, alloc;
	char	*kwval;

	if (kwval_lookup(kw, &kwval, &cat, &type, &alloc) == 0) {
		/*
		 * invalid keyword specified.
		 * XXX: any actions?
		 */
		fprintf(stderr, "Unknown keyword: `%s'\n", kw);
		return;
	}

	if (prt_categories) {
		if (prt_keywords)
			printf("%-20s ", lookup_localecat(cat));
		else
			printf("%-20s\t%s\n", kw, lookup_localecat(cat));
	}

	if (prt_keywords) {
		switch (type) {
		case TYPE_NUM:
			tmpval = (char)*kwval;
			printf("%s=%d\n", kw, tmpval);
			break;
		case TYPE_STR:
			printf("%s=\"%s\"\n", kw, kwval);
			break;
		case TYPE_UNQ:
			printf("%s=%s\n", kw, kwval);
			break;
		}
	}

	if (!prt_categories && !prt_keywords) {
		switch (type) {
		case TYPE_NUM:
			tmpval = (char)*kwval;
			printf("%d\n", tmpval);
			break;
		case TYPE_STR:
		case TYPE_UNQ:
			printf("%s\n", kwval);
			break;
		}
	}

	if (alloc)
		free(kwval);
}