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
struct TYPE_2__ {char* name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 size_t NLCINFO ; 
 char* getenv (char*) ; 
 TYPE_1__* lcinfo ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

void
showlocale(void)
{
	size_t	i;
	const char *lang, *vval, *eval;

	setlocale(LC_ALL, "");

	lang = getenv("LANG");
	if (lang == NULL) {
		lang = "";
	}
	printf("LANG=%s\n", lang);
	/* XXX: if LANG is null, then set it to "C" to get implied values? */

	for (i = 0; i < NLCINFO; i++) {
		vval = setlocale(lcinfo[i].id, NULL);
		eval = getenv(lcinfo[i].name);
		if (eval != NULL && !strcmp(eval, vval)
				&& strcmp(lang, vval)) {
			/*
			 * Appropriate environment variable set, its value
			 * is valid and not overridden by LC_ALL
			 *
			 * XXX: possible side effect: if both LANG and
			 * overridden environment variable are set into same
			 * value, then it'll be assumed as 'implied'
			 */
			printf("%s=%s\n", lcinfo[i].name, vval);
		} else {
			printf("%s=\"%s\"\n", lcinfo[i].name, vval);
		}
	}

	vval = getenv("LC_ALL");
	if (vval == NULL) {
		vval = "";
	}
	printf("LC_ALL=%s\n", vval);
}