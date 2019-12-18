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
struct option {char* name; char* value; } ;

/* Variables and functions */
 char* OPTIONINDENT ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 struct option* optiontab ; 
 int /*<<< orphan*/  set_option (char*,char*,int) ; 
 int /*<<< orphan*/  ttyout ; 

void
setoption(int argc, char *argv[])
{
	struct option *o;

	code = -1;
	if (argc == 0 || (argc != 1 && argc != 3)) {
		UPRINTF("usage: %s [option value]\n", argv[0]);
		return;
	}

#define	OPTIONINDENT ((int) sizeof("http_proxy"))
	if (argc == 1) {
		for (o = optiontab; o->name != NULL; o++) {
			fprintf(ttyout, "%-*s\t%s\n", OPTIONINDENT,
			    o->name, o->value ? o->value : "");
		}
	} else {
		set_option(argv[1], argv[2], 1);
	}
	code = 0;
}