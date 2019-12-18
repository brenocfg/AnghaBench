#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  rootfd; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int openat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static void
rmopie(char const * name)
{
	char tmp[1014];
	FILE *fp;
	int fd;
	size_t len;
	off_t	atofs = 0;
	
	if ((fd = openat(conf.rootfd, "etc/opiekeys", O_RDWR)) == -1)
		return;

	fp = fdopen(fd, "r+");
	len = strlen(name);

	while (fgets(tmp, sizeof(tmp), fp) != NULL) {
		if (strncmp(name, tmp, len) == 0 && tmp[len]==' ') {
			/* Comment username out */
			if (fseek(fp, atofs, SEEK_SET) == 0)
				fwrite("#", 1, 1, fp);
			break;
		}
		atofs = ftell(fp);
	}
	/*
	 * If we got an error of any sort, don't update!
	 */
	fclose(fp);
}