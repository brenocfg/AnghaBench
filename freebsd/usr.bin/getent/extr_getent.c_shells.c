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
 int RV_NOTFOUND ; 
 int RV_OK ; 
 int /*<<< orphan*/  SHELLSPRINT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  endusershell () ; 
 char* getusershell () ; 
 int /*<<< orphan*/  setusershell () ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
shells(int argc, char *argv[])
{
	const char	*sh;
	int		i, rv;

	assert(argc > 1);
	assert(argv != NULL);

#define SHELLSPRINT	printf("%s\n", sh)

	setusershell();
	rv = RV_OK;
	if (argc == 2) {
		while ((sh = getusershell()) != NULL)
			SHELLSPRINT;
	} else {
		for (i = 2; i < argc; i++) {
			setusershell();
			while ((sh = getusershell()) != NULL) {
				if (strcmp(sh, argv[i]) == 0) {
					SHELLSPRINT;
					break;
				}
			}
			if (sh == NULL) {
				rv = RV_NOTFOUND;
				break;
			}
		}
	}
	endusershell();
	return rv;
}