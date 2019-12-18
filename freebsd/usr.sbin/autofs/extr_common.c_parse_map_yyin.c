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
 char* checked_strdup (char const*) ; 
 int lineno ; 
 int /*<<< orphan*/  log_debugx (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  log_errx (int,char*,char const*,int) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*,int) ; 
 struct node* node_new (struct node*,char*,char*,char*,char const*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int yylex () ; 
 char* yytext ; 

__attribute__((used)) static void
parse_map_yyin(struct node *parent, const char *map, const char *executable_key)
{
	char *key = NULL, *options = NULL, *mountpoint = NULL,
	    *options2 = NULL, *location = NULL;
	int ret;
	struct node *node;

	lineno = 1;

	if (executable_key != NULL)
		key = checked_strdup(executable_key);

	for (;;) {
		ret = yylex();
		if (ret == 0 || ret == NEWLINE) {
			/*
			 * In case of executable map, the key is always
			 * non-NULL, even if the map is empty.  So, make sure
			 * we don't fail empty maps here.
			 */
			if ((key != NULL && executable_key == NULL) ||
			    options != NULL) {
				log_errx(1, "truncated entry at %s, line %d",
				    map, lineno);
			}
			if (ret == 0 || executable_key != NULL) {
				/*
				 * End of file.
				 */
				break;
			} else {
				key = options = NULL;
				continue;
			}
		}
		if (key == NULL) {
			key = checked_strdup(yytext);
			if (key[0] == '+') {
				node_new(parent, key, NULL, NULL, map, lineno);
				key = options = NULL;
				continue;
			}
			continue;
		} else if (yytext[0] == '-') {
			if (options != NULL) {
				log_errx(1, "duplicated options at %s, line %d",
				    map, lineno);
			}
			/*
			 * +1 to skip leading "-".
			 */
			options = checked_strdup(yytext + 1);
			continue;
		}

		/*
		 * We cannot properly handle a situation where the map key
		 * is "/".  Ignore such entries.
		 *
		 * XXX: According to Piete Brooks, Linux automounter uses
		 *	"/" as a wildcard character in LDAP maps.  Perhaps
		 *	we should work around this braindamage by substituting
		 *	"*" for "/"?
		 */
		if (strcmp(key, "/") == 0) {
			log_warnx("nonsensical map key \"/\" at %s, line %d; "
			    "ignoring map entry ", map, lineno);

			/*
			 * Skip the rest of the entry.
			 */
			do {
				ret = yylex();
			} while (ret != 0 && ret != NEWLINE);

			key = options = NULL;
			continue;
		}

		//log_debugx("adding map node, %s", key);
		node = node_new(parent, key, options, NULL, map, lineno);
		key = options = NULL;

		for (;;) {
			if (yytext[0] == '/') {
				if (mountpoint != NULL) {
					log_errx(1, "duplicated mountpoint "
					    "in %s, line %d", map, lineno);
				}
				if (options2 != NULL || location != NULL) {
					log_errx(1, "mountpoint out of order "
					    "in %s, line %d", map, lineno);
				}
				mountpoint = checked_strdup(yytext);
				goto again;
			}

			if (yytext[0] == '-') {
				if (options2 != NULL) {
					log_errx(1, "duplicated options "
					    "in %s, line %d", map, lineno);
				}
				if (location != NULL) {
					log_errx(1, "options out of order "
					    "in %s, line %d", map, lineno);
				}
				options2 = checked_strdup(yytext + 1);
				goto again;
			}

			if (location != NULL) {
				log_errx(1, "too many arguments "
				    "in %s, line %d", map, lineno);
			}

			/*
			 * If location field starts with colon, e.g. ":/dev/cd0",
			 * then strip it.
			 */
			if (yytext[0] == ':') {
				location = checked_strdup(yytext + 1);
				if (location[0] == '\0') {
					log_errx(1, "empty location in %s, "
					    "line %d", map, lineno);
				}
			} else {
				location = checked_strdup(yytext);
			}

			if (mountpoint == NULL)
				mountpoint = checked_strdup("/");
			if (options2 == NULL)
				options2 = checked_strdup("");

#if 0
			log_debugx("adding map node, %s %s %s",
			    mountpoint, options2, location);
#endif
			node_new(node, mountpoint, options2, location,
			    map, lineno);
			mountpoint = options2 = location = NULL;
again:
			ret = yylex();
			if (ret == 0 || ret == NEWLINE) {
				if (mountpoint != NULL || options2 != NULL ||
				    location != NULL) {
					log_errx(1, "truncated entry "
					    "in %s, line %d", map, lineno);
				}
				break;
			}
		}
	}
}