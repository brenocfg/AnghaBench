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
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ld_path_libmap_conf ; 
 scalar_t__ lm_count ; 
 int /*<<< orphan*/  lmc_parse (char*,int) ; 
 int /*<<< orphan*/  lmc_parse_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmp_head ; 
 char* xstrdup (char*) ; 

int
lm_init(char *libmap_override)
{
	char *p;

	dbg("lm_init(\"%s\")", libmap_override);
	TAILQ_INIT(&lmp_head);

	lmc_parse_file(ld_path_libmap_conf);

	if (libmap_override) {
		/*
		 * Do some character replacement to make $LDLIBMAP look
		 * like a text file, then parse it.
		 */
		libmap_override = xstrdup(libmap_override);
		for (p = libmap_override; *p; p++) {
			switch (*p) {
			case '=':
				*p = ' ';
				break;
			case ',':
				*p = '\n';
				break;
			}
		}
		lmc_parse(libmap_override, p - libmap_override);
		free(libmap_override);
	}

	return (lm_count == 0);
}