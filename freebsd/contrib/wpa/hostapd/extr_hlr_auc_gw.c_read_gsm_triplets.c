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
struct gsm_triplet {struct gsm_triplet* next; int /*<<< orphan*/  _rand; int /*<<< orphan*/  sres; int /*<<< orphan*/  kc; int /*<<< orphan*/  imsi; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 struct gsm_triplet* gsm_db ; 
 scalar_t__ hexstr2bin (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_free (struct gsm_triplet*) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int os_strlen (char*) ; 
 struct gsm_triplet* os_zalloc (int) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 char* str_token (char*,char*,char**) ; 

__attribute__((used)) static int read_gsm_triplets(const char *fname)
{
	FILE *f;
	char buf[200], *pos, *pos2;
	struct gsm_triplet *g = NULL;
	int line, ret = 0;

	if (fname == NULL)
		return -1;

	f = fopen(fname, "r");
	if (f == NULL) {
		printf("Could not open GSM triplet data file '%s'\n", fname);
		return -1;
	}

	line = 0;
	while (fgets(buf, sizeof(buf), f)) {
		line++;

		/* Parse IMSI:Kc:SRES:RAND */
		buf[sizeof(buf) - 1] = '\0';
		if (buf[0] == '#')
			continue;
		pos = buf;
		while (*pos != '\0' && *pos != '\n')
			pos++;
		if (*pos == '\n')
			*pos = '\0';
		pos = buf;
		if (*pos == '\0')
			continue;

		g = os_zalloc(sizeof(*g));
		if (g == NULL) {
			ret = -1;
			break;
		}

		/* IMSI */
		pos2 = NULL;
		pos = str_token(buf, ":", &pos2);
		if (!pos || os_strlen(pos) >= sizeof(g->imsi)) {
			printf("%s:%d - Invalid IMSI\n", fname, line);
			ret = -1;
			break;
		}
		os_strlcpy(g->imsi, pos, sizeof(g->imsi));

		/* Kc */
		pos = str_token(buf, ":", &pos2);
		if (!pos || os_strlen(pos) != 16 || hexstr2bin(pos, g->kc, 8)) {
			printf("%s:%d - Invalid Kc\n", fname, line);
			ret = -1;
			break;
		}

		/* SRES */
		pos = str_token(buf, ":", &pos2);
		if (!pos || os_strlen(pos) != 8 ||
		    hexstr2bin(pos, g->sres, 4)) {
			printf("%s:%d - Invalid SRES\n", fname, line);
			ret = -1;
			break;
		}

		/* RAND */
		pos = str_token(buf, ":", &pos2);
		if (!pos || os_strlen(pos) != 32 ||
		    hexstr2bin(pos, g->_rand, 16)) {
			printf("%s:%d - Invalid RAND\n", fname, line);
			ret = -1;
			break;
		}

		g->next = gsm_db;
		gsm_db = g;
		g = NULL;
	}
	os_free(g);

	fclose(f);

	return ret;
}