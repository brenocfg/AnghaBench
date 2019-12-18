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
struct member_entry {char* key; char* domain; struct member_entry* next; struct grouplist* groups; } ;
struct grouplist {char* groupname; struct grouplist* next; } ;
struct group_entry {struct group_entry* next; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  readbuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LINSIZ ; 
 int TABLESIZE ; 
 int /*<<< orphan*/  __endnetgrent () ; 
 scalar_t__ __getnetgrent (char**,char**,char**) ; 
 int /*<<< orphan*/  __setnetgrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getopt (int,char**,char*) ; 
 struct group_entry** gtable ; 
 int /*<<< orphan*/  mstore (struct member_entry**,char*,int /*<<< orphan*/ ,char*) ; 
 struct member_entry** mtable ; 
 char* netgroup ; 
 char* optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  store (struct group_entry**,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strpbrk (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	FILE *fp;
	char readbuf[LINSIZ];
	struct group_entry *gcur;
	struct member_entry *mcur;
	char *host, *user, *domain;
	int ch;
	char *key = NULL, *data = NULL;
	int hosts = -1, i;

	if (argc < 2)
		usage();

	while ((ch = getopt(argc, argv, "uhf:")) != -1) {
		switch(ch) {
		case 'u':
			if (hosts != -1) {
				warnx("please use only one of -u or -h");
				usage();
			}
			hosts = 0;
			break;
		case 'h':
			if (hosts != -1) {
				warnx("please use only one of -u or -h");
				usage();
			}
			hosts = 1;
			break;
		case 'f':
			netgroup = optarg;
			break;
		default:
			usage();
			break;
		}
	}

	if (hosts == -1)
		usage();

	if (strcmp(netgroup, "-")) {
		if ((fp = fopen(netgroup, "r")) == NULL) {
			err(1, "%s", netgroup);
		}
	} else {
		fp = stdin;
	}

	/* Stuff all the netgroup names and members into a hash table. */
	while (fgets(readbuf, LINSIZ, fp)) {
		if (readbuf[0] == '#')
			continue;
		/* handle backslash line continuations */
		while(readbuf[strlen(readbuf) - 2] == '\\') {
			fgets((char *)&readbuf[strlen(readbuf) - 2],
					sizeof(readbuf) - strlen(readbuf), fp);
		}
		data = NULL;
		if ((data = (char *)(strpbrk(readbuf, " \t") + 1)) < (char *)2)
			continue;
		key = (char *)&readbuf;
		*(data - 1) = '\0';
		store(gtable, key, data);
	}

	fclose(fp);

	/*
	 * Find all members of each netgroup and keep track of which
	 * group they belong to.
	 */
	for (i = 0; i < TABLESIZE; i++) {
		gcur = gtable[i];
		while(gcur) {
			__setnetgrent(gcur->key);
			while(__getnetgrent(&host, &user, &domain) != 0) {
				if (hosts ? host && strcmp(host,"-") : user && strcmp(user, "-"))
					mstore(mtable, hosts ? host : user, gcur->key, domain);
			}
			gcur = gcur->next;
		}
	}

	/* Release resources used by the netgroup parser code. */
	__endnetgrent();

	/* Spew out the results. */
	for (i = 0; i < TABLESIZE; i++) {
		mcur = mtable[i];
		while(mcur) {
			struct grouplist *tmp;
			printf ("%s.%s\t", mcur->key, mcur->domain);
			tmp = mcur->groups;
			while(tmp) {
				printf ("%s", tmp->groupname);
				tmp = tmp->next;
				if (tmp)
					printf(",");
			}
			mcur = mcur->next;
			printf ("\n");
		}
	}

	/* Let the OS free all our resources. */
	exit(0);
}