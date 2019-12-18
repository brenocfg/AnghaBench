#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t sl_cur; char** sl_str; } ;
struct TYPE_6__ {char** sl_str; size_t sl_cur; } ;
typedef  TYPE_1__ StringList ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  init_locales_list () ; 
 TYPE_5__* locales ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  qsort (char**,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmp ; 
 int /*<<< orphan*/  sl_add (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * sl_find (TYPE_1__*,char*) ; 
 TYPE_1__* sl_init () ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 

void
list_charmaps(void)
{
	size_t i;
	char *s, *cs;
	StringList *charmaps;

	/* initialize StringList */
	charmaps = sl_init();
	if (charmaps == NULL)
		err(1, "could not allocate memory");

	/* fetch locales list */
	init_locales_list();

	/* split codesets and build their list */
	for (i = 0; i < locales->sl_cur; i++) {
		s = locales->sl_str[i];
		if ((cs = strchr(s, '.')) != NULL) {
			cs++;
			if (sl_find(charmaps, cs) == NULL)
				sl_add(charmaps, cs);
		}
	}

	/* add US-ASCII, if not yet added */
	if (sl_find(charmaps, "US-ASCII") == NULL)
		sl_add(charmaps, strdup("US-ASCII"));

	/* sort the list */
	qsort(charmaps->sl_str, charmaps->sl_cur, sizeof(char *), scmp);

	/* print results */
	for (i = 0; i < charmaps->sl_cur; i++) {
		printf("%s\n", charmaps->sl_str[i]);
	}
}