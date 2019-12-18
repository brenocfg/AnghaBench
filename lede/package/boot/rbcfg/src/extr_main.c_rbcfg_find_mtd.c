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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  dev ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int S_IFBLK ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int sscanf (char*,char*,int*,int*) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strstr (char*,char const*) ; 

char *rbcfg_find_mtd(const char *name, int *erase_size)
{
	FILE *f;
	int mtd_num;
	char dev[PATH_MAX];
	char *ret = NULL;
	struct stat s;
	int err;

	f = fopen("/proc/mtd", "r");
	if (!f)
		return NULL;

	while (1) {
		char *p;
		p = fgets(dev, sizeof(dev), f);
		if (!p)
			break;

		if (!strstr(dev, name))
			continue;

		err = sscanf(dev, "mtd%d: %08x", &mtd_num, erase_size);
		if (err != 2)
			break;

		sprintf(dev, "/dev/mtdblock%d", mtd_num);
		err = stat(dev, &s);
		if (err < 0)
			break;

		if ((s.st_mode & S_IFBLK) == 0)
			break;

		ret = malloc(strlen(dev) + 1);
		if (ret == NULL)
			break;

		strncpy(ret, dev, strlen(dev) + 1);
		break;
	}

	fclose(f);
	return ret;
}