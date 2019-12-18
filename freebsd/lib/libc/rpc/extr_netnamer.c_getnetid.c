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
 int /*<<< orphan*/  NETID ; 
 char* NETIDFILE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int yp_get_default_domain (char**) ; 
 int yp_match (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char**,int*) ; 

int
getnetid(char *key, char *ret)
{
	char            buf[1024];	/* big enough */
	char           *res;
	char           *mkey;
	char           *mval;
	FILE           *fd;
#ifdef YP
	char           *domain;
	int             err;
	char           *lookup;
	int             len;
#endif
	int rv;

	rv = 0;

	fd = fopen(NETIDFILE, "r");
	if (fd == NULL) {
#ifdef YP
		res = "+";
		goto getnetidyp;
#else
		return (0);
#endif
	}
	while (fd != NULL) {
		res = fgets(buf, sizeof(buf), fd);
		if (res == NULL) {
			rv = 0;
			goto done;
		}
		if (res[0] == '#')
			continue;
		else if (res[0] == '+') {
#ifdef YP
	getnetidyp:
			err = yp_get_default_domain(&domain);
			if (err) {
				continue;
			}
			lookup = NULL;
			err = yp_match(domain, NETID, key,
				strlen(key), &lookup, &len);
			if (err) {
#ifdef DEBUG
				fprintf(stderr, "match failed error %d\n", err);
#endif
				continue;
			}
			lookup[len] = 0;
			strcpy(ret, lookup);
			free(lookup);
			rv = 2;
			goto done;
#else	/* YP */
#ifdef DEBUG
			fprintf(stderr,
"Bad record in %s '+' -- NIS not supported in this library copy\n",
				NETIDFILE);
#endif
			continue;
#endif	/* YP */
		} else {
			mkey = strsep(&res, "\t ");
			if (mkey == NULL) {
				fprintf(stderr,
		"Bad record in %s -- %s", NETIDFILE, buf);
				continue;
			}
			do {
				mval = strsep(&res, " \t#\n");
			} while (mval != NULL && !*mval);
			if (mval == NULL) {
				fprintf(stderr,
		"Bad record in %s val problem - %s", NETIDFILE, buf);
				continue;
			}
			if (strcmp(mkey, key) == 0) {
				strcpy(ret, mval);
				rv = 1;
				goto done;
			}
		}
	}

done:
	if (fd != NULL)
		fclose(fd);
	return (rv);
}