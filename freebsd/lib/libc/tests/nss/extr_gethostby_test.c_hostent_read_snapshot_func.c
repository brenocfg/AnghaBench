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
struct hostent {int h_addrtype; int h_length; int /*<<< orphan*/  h_addr_list; int /*<<< orphan*/  h_aliases; int /*<<< orphan*/ * h_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  sl_str; } ;
typedef  TYPE_1__ StringList ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_hostent (struct hostent*) ; 
 int hostent_read_snapshot_addr (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (struct hostent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sl_add (TYPE_1__*,char*) ; 
 TYPE_1__* sl_init () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int
hostent_read_snapshot_func(struct hostent *ht, char *line)
{
	StringList *sl1, *sl2;
	char *s, *ps, *ts;
	int i, rv;

#ifdef DEBUG
	printf("1 line read from snapshot:\n%s\n", line);
#endif

	rv = 0;
	i = 0;
	sl1 = sl2 = NULL;
	ps = line;
	memset(ht, 0, sizeof(struct hostent));
	while ((s = strsep(&ps, " ")) != NULL) {
		switch (i) {
		case 0:
			ht->h_name = strdup(s);
			ATF_REQUIRE(ht->h_name != NULL);
			break;

		case 1:
			ht->h_addrtype = (int)strtol(s, &ts, 10);
			if (*ts != '\0')
				goto fin;
			break;

		case 2:
			ht->h_length = (int)strtol(s, &ts, 10);
			if (*ts != '\0')
				goto fin;
			break;

		case 3:
			if (sl1 == NULL) {
				if (strcmp(s, "(null)") == 0)
					return (0);

				sl1 = sl_init();
				ATF_REQUIRE(sl1 != NULL);

				if (strcmp(s, "noaliases") != 0) {
					ts = strdup(s);
					ATF_REQUIRE(ts != NULL);
					sl_add(sl1, ts);
				}
			} else {
				if (strcmp(s, ":") == 0)
					++i;
				else {
					ts = strdup(s);
					ATF_REQUIRE(ts != NULL);
					sl_add(sl1, ts);
				}
			}
			break;

		case 4:
			if (sl2 == NULL) {
				if (strcmp(s, "(null)") == 0)
					return (0);

				sl2 = sl_init();
				ATF_REQUIRE(sl2 != NULL);

				if (strcmp(s, "noaddrs") != 0) {
					ts = calloc(1, ht->h_length);
					ATF_REQUIRE(ts != NULL);
					rv = hostent_read_snapshot_addr(s,
					    (unsigned char *)ts,
					    ht->h_length);
					sl_add(sl2, ts);
					if (rv != 0)
						goto fin;
				}
			} else {
				ts = calloc(1, ht->h_length);
				ATF_REQUIRE(ts != NULL);
				rv = hostent_read_snapshot_addr(s,
				    (unsigned char *)ts, ht->h_length);
				sl_add(sl2, ts);
				if (rv != 0)
					goto fin;
			}
			break;
		default:
			break;
		}

		if (i != 3 && i != 4)
			++i;
	}

fin:
	if (sl1 != NULL) {
		sl_add(sl1, NULL);
		ht->h_aliases = sl1->sl_str;
	}
	if (sl2 != NULL) {
		sl_add(sl2, NULL);
		ht->h_addr_list = sl2->sl_str;
	}

	if ((i != 4) || (rv != 0)) {
		free_hostent(ht);
		memset(ht, 0, sizeof(struct hostent));
		return (-1);
	}

	/* NOTE: is it a dirty hack or not? */
	free(sl1);
	free(sl2);
	return (0);
}