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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* PKFILE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strsep (char**,char*) ; 
 int yp_get_default_domain (char**) ; 
 int yp_match (char*,char*,char const*,int /*<<< orphan*/ ,char**,int*) ; 

int
getpublicandprivatekey(const char *key, char *ret)
{
	char buf[1024];	/* big enough */
	char *res;
	FILE *fd;
	char *mkey;
	char *mval;

	fd = fopen(PKFILE, "r");
	if (fd == NULL)
		return (0);
	for (;;) {
		res = fgets(buf, sizeof(buf), fd);
		if (res == NULL) {
			fclose(fd);
			return (0);
		}
		if (res[0] == '#')
			continue;
		else if (res[0] == '+') {
#ifdef YP
			char *PKMAP = "publickey.byname";
			char *lookup;
			char *domain;
			int err;
			int len;

			err = yp_get_default_domain(&domain);
			if (err) {
				continue;
			}
			lookup = NULL;
			err = yp_match(domain, PKMAP, key, strlen(key), &lookup, &len);
			if (err) {
#ifdef DEBUG
				fprintf(stderr, "match failed error %d\n", err);
#endif
				continue;
			}
			lookup[len] = 0;
			strcpy(ret, lookup);
			fclose(fd);
			free(lookup);
			return (2);
#else /* YP */
#ifdef DEBUG
			fprintf(stderr,
"Bad record in %s '+' -- NIS not supported in this library copy\n", PKFILE);
#endif /* DEBUG */
			continue;
#endif /* YP */
		} else {
			mkey = strsep(&res, "\t ");
			if (mkey == NULL) {
				fprintf(stderr,
				"Bad record in %s -- %s", PKFILE, buf);
				continue;
			}
			do {
				mval = strsep(&res, " \t#\n");
			} while (mval != NULL && !*mval);
			if (mval == NULL) {
				fprintf(stderr,
			"Bad record in %s val problem - %s", PKFILE, buf);
				continue;
			}
			if (strcmp(mkey, key) == 0) {
				strcpy(ret, mval);
				fclose(fd);
				return (1);
			}
		}
	}
}