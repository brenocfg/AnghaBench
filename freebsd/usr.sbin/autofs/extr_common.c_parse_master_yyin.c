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
struct node {int dummy; } ;

/* Variables and functions */
 int NEWLINE ; 
 char* checked_strdup (scalar_t__) ; 
 scalar_t__ lineno ; 
 int /*<<< orphan*/  log_errx (int,char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  node_new_map (struct node*,char*,char*,char*,char const*,scalar_t__) ; 
 int yylex () ; 
 scalar_t__ yytext ; 

__attribute__((used)) static void
parse_master_yyin(struct node *root, const char *master)
{
	char *mountpoint = NULL, *map = NULL, *options = NULL;
	int ret;

	/*
	 * XXX: 1 gives incorrect values; wtf?
	 */
	lineno = 0;

	for (;;) {
		ret = yylex();
		if (ret == 0 || ret == NEWLINE) {
			if (mountpoint != NULL) {
				//log_debugx("adding map for %s", mountpoint);
				node_new_map(root, mountpoint, options, map,
				    master, lineno);
			}
			if (ret == 0) {
				break;
			} else {
				mountpoint = map = options = NULL;
				continue;
			}
		}
		if (mountpoint == NULL) {
			mountpoint = checked_strdup(yytext);
		} else if (map == NULL) {
			map = checked_strdup(yytext);
		} else if (options == NULL) {
			/*
			 * +1 to skip leading "-".
			 */
			options = checked_strdup(yytext + 1);
		} else {
			log_errx(1, "too many arguments at %s, line %d",
			    master, lineno);
		}
	}
}