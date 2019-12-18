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
struct TYPE_2__ {int catid; int type; int source; int /*<<< orphan*/  value_ref; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char CHAR_MAX ; 
 size_t NKWINFO ; 
#define  SRC_LCONV 130 
#define  SRC_LINFO 129 
#define  SRC_LTIME 128 
 int TYPE_NUM ; 
 int TYPE_UNQ ; 
 TYPE_1__* kwinfo ; 
 char* kwval_lconv (int /*<<< orphan*/ ) ; 
 char* kwval_ltime (int /*<<< orphan*/ ) ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

int
kwval_lookup(const char *kwname, char **kwval, int *cat, int *type, int *alloc)
{
	int	rval;
	size_t	i;
	static char nastr[3] = "-1";

	rval = 0;
	*alloc = 0;
	for (i = 0; i < NKWINFO; i++) {
		if (strcasecmp(kwname, kwinfo[i].name) == 0) {
			rval = 1;
			*cat = kwinfo[i].catid;
			*type = kwinfo[i].type;
			switch (kwinfo[i].source) {
			case SRC_LINFO:
				*kwval = nl_langinfo(kwinfo[i].value_ref);
				break;
			case SRC_LCONV:
				*kwval = kwval_lconv(kwinfo[i].value_ref);
				/*
				 * XXX This check will need to be modified
				 * if/when localeconv() is fixed (PR172215).
				 */
				if (**kwval == CHAR_MAX) {
					if (*type == TYPE_NUM)
						*type = TYPE_UNQ;
					*kwval = nastr;
				}
				break;
			case SRC_LTIME:
				*kwval = kwval_ltime(kwinfo[i].value_ref);
				*alloc = 1;
				break;
			}
			break;
		}
	}

	return (rval);
}