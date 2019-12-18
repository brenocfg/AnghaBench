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
typedef  int /*<<< orphan*/  k ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_FILE ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int,int) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int write (int,char*,int) ; 

void save_key(unsigned char *key, int len)
{
	char tmp[16];
	char k[64];
	int fd;
	int rd;

	assert(len*3 < sizeof(k));

	k[0] = 0;
	while (len--) {
		sprintf(tmp, "%.2X", *key++);
		strcat(k, tmp);
		if (len)
			strcat(k, ":");
	}

	fd = open(KEY_FILE, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		err(1, "open()");

	printf("\nKey: %s\n", k);
	rd = write(fd, k, strlen(k));
	if (rd == -1)
		err(1, "write()");
	if (rd != strlen(k))
		errx(1, "write %d/%d\n", rd, strlen(k));
	close(fd);
}