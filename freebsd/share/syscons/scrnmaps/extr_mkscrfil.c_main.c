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
typedef  int /*<<< orphan*/  scrmap_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  scrmap ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
	FILE *fd;

	if (argc == 2) {
		if ((fd = fopen(argv[1], "w")) == NULL) {
			perror(argv[1]);
			return 1;
		}
		fwrite(&scrmap, sizeof(scrmap_t), 1, fd);
		fclose(fd);
		return 0;
	}
	else {
		fprintf(stderr, "usage: %s <mapfile>\n", argv[0]);
		return 1;
	}
}