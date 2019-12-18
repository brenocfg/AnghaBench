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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *saveRead(int file, off_t offset, off_t len, char *name)
{
	char *tmp;
	int count;
	off_t off;
	if ((off = lseek(file, offset, SEEK_SET)) < 0) {
		fprintf(stderr, "%s: fseek: %s\n", name, strerror(errno));
		exit(1);
	}
	if (!(tmp = (char *) malloc(len))) {
		fprintf(stderr, "%s: Can't allocate %ld bytes.\n", name,
			len);
		exit(1);
	}
	count = read(file, tmp, len);
	if (count != len) {
		fprintf(stderr, "%s: read: %s.\n",
			name,
			count ? strerror(errno) : "End of file reached");
		exit(1);
	}
	return tmp;
}