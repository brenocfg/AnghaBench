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
struct pci_vendor_info {int id; int /*<<< orphan*/  devs; int /*<<< orphan*/ * desc; } ;
struct pci_device_info {int id; int /*<<< orphan*/  devs; int /*<<< orphan*/ * desc; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pci_vendor_info*,int /*<<< orphan*/ ) ; 
 char* _PATH_LPCIVDB ; 
 char* _PATH_PCIVDB ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (struct pci_vendor_info*) ; 
 char* getenv (char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  link ; 
 struct pci_vendor_info* malloc (int) ; 
 int /*<<< orphan*/  pci_vendors ; 
 int sscanf (char*,char*,int*,char*) ; 
 char* strchr (char*,char) ; 
 void* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
load_vendors(void)
{
	const char *dbf;
	FILE *db;
	struct pci_vendor_info *cv;
	struct pci_device_info *cd;
	char buf[1024], str[1024];
	char *ch;
	int id, error;

	/*
	 * Locate the database and initialise.
	 */
	TAILQ_INIT(&pci_vendors);
	if ((dbf = getenv("PCICONF_VENDOR_DATABASE")) == NULL)
		dbf = _PATH_LPCIVDB;
	if ((db = fopen(dbf, "r")) == NULL) {
		dbf = _PATH_PCIVDB;
		if ((db = fopen(dbf, "r")) == NULL)
			return(1);
	}
	cv = NULL;
	cd = NULL;
	error = 0;

	/*
	 * Scan input lines from the database
	 */
	for (;;) {
		if (fgets(buf, sizeof(buf), db) == NULL)
			break;

		if ((ch = strchr(buf, '#')) != NULL)
			*ch = '\0';
		ch = strchr(buf, '\0') - 1;
		while (ch > buf && isspace(*ch))
			*ch-- = '\0';
		if (ch <= buf)
			continue;

		/* Can't handle subvendor / subdevice entries yet */
		if (buf[0] == '\t' && buf[1] == '\t')
			continue;

		/* Check for vendor entry */
		if (buf[0] != '\t' && sscanf(buf, "%04x %[^\n]", &id, str) == 2) {
			if ((id == 0) || (strlen(str) < 1))
				continue;
			if ((cv = malloc(sizeof(struct pci_vendor_info))) == NULL) {
				warn("allocating vendor entry");
				error = 1;
				break;
			}
			if ((cv->desc = strdup(str)) == NULL) {
				free(cv);
				warn("allocating vendor description");
				error = 1;
				break;
			}
			cv->id = id;
			TAILQ_INIT(&cv->devs);
			TAILQ_INSERT_TAIL(&pci_vendors, cv, link);
			continue;
		}

		/* Check for device entry */
		if (buf[0] == '\t' && sscanf(buf + 1, "%04x %[^\n]", &id, str) == 2) {
			if ((id == 0) || (strlen(str) < 1))
				continue;
			if (cv == NULL) {
				warnx("device entry with no vendor!");
				continue;
			}
			if ((cd = malloc(sizeof(struct pci_device_info))) == NULL) {
				warn("allocating device entry");
				error = 1;
				break;
			}
			if ((cd->desc = strdup(str)) == NULL) {
				free(cd);
				warn("allocating device description");
				error = 1;
				break;
			}
			cd->id = id;
			TAILQ_INSERT_TAIL(&cv->devs, cd, link);
			continue;
		}

		/* It's a comment or junk, ignore it */
	}
	if (ferror(db))
		error = 1;
	fclose(db);

	return(error);
}