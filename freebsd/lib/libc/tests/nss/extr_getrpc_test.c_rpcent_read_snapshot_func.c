#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpcent {int r_number; int /*<<< orphan*/  r_aliases; TYPE_1__* r_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  sl_str; } ;
typedef  TYPE_1__ StringList ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct rpcent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sl_add (TYPE_1__*,char*) ; 
 TYPE_1__* sl_init () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int
rpcent_read_snapshot_func(struct rpcent *rpc, char *line)
{
	StringList *sl;
	char *s, *ps, *ts;
	int i;

	printf("1 line read from snapshot:\n%s\n", line);

	i = 0;
	sl = NULL;
	ps = line;
	memset(rpc, 0, sizeof(struct rpcent));
	while ((s = strsep(&ps, " ")) != NULL) {
		switch (i) {
		case 0:
				rpc->r_name = strdup(s);
				ATF_REQUIRE(rpc->r_name != NULL);
			break;

		case 1:
			rpc->r_number = (int)strtol(s, &ts, 10);
			if (*ts != '\0') {
				free(rpc->r_name);
				return (-1);
			}
			break;

		default:
			if (sl == NULL) {
				if (strcmp(s, "(null)") == 0)
					return (0);

				sl = sl_init();
				ATF_REQUIRE(sl != NULL);

				if (strcmp(s, "noaliases") != 0) {
					ts = strdup(s);
					ATF_REQUIRE(ts != NULL);
					sl_add(sl, ts);
				}
			} else {
				ts = strdup(s);
				ATF_REQUIRE(ts != NULL);
				sl_add(sl, ts);
			}
			break;
		}
		i++;
	}

	if (i < 3) {
		free(rpc->r_name);
		memset(rpc, 0, sizeof(struct rpcent));
		return (-1);
	}

	sl_add(sl, NULL);
	rpc->r_aliases = sl->sl_str;

	/* NOTE: is it a dirty hack or not? */
	free(sl);
	return (0);
}