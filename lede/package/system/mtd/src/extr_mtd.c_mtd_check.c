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

/* Variables and functions */
 scalar_t__ buf ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  erasesize ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int mtd_check_open (char const*) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int mtd_check(const char *mtd)
{
	char *next = NULL;
	char *str = NULL;
	int fd;

	if (strchr(mtd, ':')) {
		str = strdup(mtd);
		mtd = str;
	}

	do {
		next = strchr(mtd, ':');
		if (next) {
			*next = 0;
			next++;
		}

		fd = mtd_check_open(mtd);
		if (fd < 0)
			return 0;

		if (!buf)
			buf = malloc(erasesize);

		close(fd);
		mtd = next;
	} while (next);

	if (str)
		free(str);

	return 1;
}