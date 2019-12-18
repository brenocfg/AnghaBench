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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ ) ; 
 int lineno ; 
 int /*<<< orphan*/  log_debugx (char*,char*) ; 
 int /*<<< orphan*/  node_new (struct node*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int) ; 
 char* strndup (char*,int) ; 
 int /*<<< orphan*/  yyin ; 

__attribute__((used)) static void
parse_map_keys_yyin(struct node *parent, const char *map)
{
	char *line = NULL, *key;
	size_t linecap = 0;
	ssize_t linelen;

	lineno = 1;

	for (;;) {
		linelen = getline(&line, &linecap, yyin);
		if (linelen < 0) {
			/*
			 * End of file.
			 */
			break;
		}
		if (linelen <= 1) {
			/*
			 * Empty line, consisting of just the newline.
			 */
			continue;
		}

		/*
		 * "-1" to strip the trailing newline.
		 */
		key = strndup(line, linelen - 1);

		log_debugx("adding key \"%s\"", key);
		node_new(parent, key, NULL, NULL, map, lineno);
		lineno++;
	}
	free(line);
}