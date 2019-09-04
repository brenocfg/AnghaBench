#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ s; scalar_t__ m; scalar_t__ l; } ;
typedef  TYPE_1__ kstring_t ;
typedef  int /*<<< orphan*/  kstream_t ;
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_SIZE ; 
 float CLOCKS_PER_SEC ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ clock () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  ks_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ ks_getuntil (int /*<<< orphan*/ *,char,TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * ks_init (int) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
	clock_t t;
	if (argc == 1) {
		fprintf(stderr, "Usage: %s <in.txt>\n", argv[0]);
		return 1;
	}
	{
		FILE *fp;
		char *s;
		t = clock();
		s = malloc(BUF_SIZE);
		fp = fopen(argv[1], "r");
		while (fgets(s, BUF_SIZE, fp));
		fclose(fp);
		fprintf(stderr, "[fgets] %.2f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);
	}
	{
		int fd, dret;
		kstream_t *ks;
		kstring_t s;
		t = clock();
		s.l = s.m = 0; s.s = 0;
		fd = open(argv[1], O_RDONLY);
		ks = ks_init(fd);
		while (ks_getuntil(ks, '\n', &s, &dret) >= 0);
		free(s.s);
		ks_destroy(ks);
		close(fd);
		fprintf(stderr, "[kstream] %.2f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);
	}
	return 0;
}