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
struct servent {int /*<<< orphan*/  s_aliases; TYPE_1__* s_proto; TYPE_1__* s_name; int /*<<< orphan*/  s_port; } ;
struct TYPE_5__ {int /*<<< orphan*/  sl_str; } ;
typedef  TYPE_1__ StringList ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memset (struct servent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sl_add (TYPE_1__*,char*) ; 
 TYPE_1__* sl_init () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int
servent_read_snapshot_func(struct servent *serv, char *line)
{
	StringList *sl;
	char *s, *ps, *ts;
	int i;

	printf("1 line read from snapshot:\n%s\n", line);

	i = 0;
	sl = NULL;
	ps = line;
	memset(serv, 0, sizeof(struct servent));
	while ( (s = strsep(&ps, " ")) != NULL) {
		switch (i) {
			case 0:
				serv->s_name = strdup(s);
				ATF_REQUIRE(serv->s_name != NULL);
			break;

			case 1:
				serv->s_port = htons(
					(int)strtol(s, &ts, 10));
				if (*ts != '\0') {
					free(serv->s_name);
					return (-1);
				}
			break;

			case 2:
				serv->s_proto = strdup(s);
				ATF_REQUIRE(serv->s_proto != NULL);
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
		++i;
	}

	if (i < 3) {
		free(serv->s_name);
		free(serv->s_proto);
		memset(serv, 0, sizeof(struct servent));
		return (-1);
	}

	sl_add(sl, NULL);
	serv->s_aliases = sl->sl_str;

	/* NOTE: is it a dirty hack or not? */
	free(sl);
	return (0);
}