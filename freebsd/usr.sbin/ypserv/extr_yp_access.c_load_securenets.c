#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* s_addr; } ;
struct TYPE_3__ {void* s_addr; } ;
struct securenet {struct securenet* next; TYPE_2__ mask; TYPE_1__ net; } ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 void* INADDR_ANY ; 
 int /*<<< orphan*/  LINEBUFSZ ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (struct securenet*) ; 
 int /*<<< orphan*/  inet_aton (char*,struct in_addr*) ; 
 struct securenet* malloc (int) ; 
 struct securenet* securenets ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int sscanf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 
 char* yp_dir ; 
 int /*<<< orphan*/  yp_error (char*,char*,...) ; 

void
load_securenets(void)
{
	FILE *fp;
	char path[MAXPATHLEN + 2];
	char linebuf[1024 + 2];
	struct securenet *tmp;

	/*
	 * If securenets is not NULL, we are being called to reload
	 * the list; free the existing list before re-reading the
	 * securenets file.
	 */
	while (securenets) {
		tmp = securenets->next;
		free(securenets);
		securenets = tmp;
	}

	snprintf(path, MAXPATHLEN, "%s/securenets", yp_dir);

	if ((fp = fopen(path, "r")) == NULL) {
		if (errno == ENOENT) {
			securenets = malloc(sizeof(struct securenet));
			securenets->net.s_addr = INADDR_ANY;
			securenets->mask.s_addr = INADDR_ANY;
			securenets->next = NULL;
			return;
		} else {
			yp_error("fopen(%s) failed: %s", path, strerror(errno));
			exit(1);
		}
	}

	securenets = NULL;

	while (fgets(linebuf, LINEBUFSZ, fp)) {
		char addr1[20], addr2[20];

		if ((linebuf[0] == '#')
		    || (strspn(linebuf, " \t\r\n") == strlen(linebuf)))
			continue;
		if (sscanf(linebuf, "%s %s", addr1, addr2) < 2) {
			yp_error("badly formatted securenets entry: %s",
							linebuf);
			continue;
		}

		tmp = malloc(sizeof(struct securenet));

		if (!inet_aton((char *)&addr1, (struct in_addr *)&tmp->net)) {
			yp_error("badly formatted securenets entry: %s", addr1);
			free(tmp);
			continue;
		}

		if (!inet_aton((char *)&addr2, (struct in_addr *)&tmp->mask)) {
			yp_error("badly formatted securenets entry: %s", addr2);
			free(tmp);
			continue;
		}

		tmp->next = securenets;
		securenets = tmp;
	}

	fclose(fp);

}