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
typedef  int /*<<< orphan*/  PORT ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  heapifyports (int /*<<< orphan*/ **,size_t,size_t) ; 
 int /*<<< orphan*/ ** malloc (size_t) ; 
 int /*<<< orphan*/ * portify (char*) ; 
 int /*<<< orphan*/  printport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  recurse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  translateport (int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	FILE * f;
	char * line;
	size_t linelen;
	PORT ** pp;	/* Array of pointers to PORTs */
	PORT * tmp;
	size_t pplen;	/* Allocated size of array */
	size_t i;

	if (argc != 2)
		usage();
	if ((f = fopen(argv[1], "r")) == NULL)
		err(1, "fopen(%s)", argv[1]);

	pplen = 1024;
	if ((pp = malloc(pplen * sizeof(PORT *))) == NULL)
		err(1, "malloc(pp)");

	/*
	 * 1. Suck in all the data, splitting into fields.
	 */
	for(i = 0; (line = fgetln(f, &linelen)) != NULL; i++) {
		if (line[linelen - 1] != '\n')
			errx(1, "Unterminated line encountered");
		line[linelen - 1] = 0;

		/* Enlarge array if needed */
		if (i >= pplen) {
			pplen *= 2;
			if ((pp = realloc(pp, pplen * sizeof(PORT *))) == NULL)
				err(1, "realloc(pp)");
		}

		pp[i] = portify(line);
	}
	/* Reallocate to the correct size */
	pplen = i;
	if ((pp = realloc(pp, pplen * sizeof(PORT *))) == NULL)
		err(1, "realloc(pp)");

	/* Make sure we actually reached the EOF */
	if (!feof(f))
		err(1, "fgetln(%s)", argv[1]);
	/* Close the describes file */
	if (fclose(f) != 0)
		err(1, "fclose(%s)", argv[1]);

	/*
	 * 1a. If there are no ports, there is no INDEX.
	 */
	if (pplen == 0)
		return 0;

	/*
	 * 2. Sort the ports according to port directory.
	 */
	for (i = pplen; i > 0; i--)
		heapifyports(pp, pplen, i - 1);	/* Build a heap */
	for (i = pplen - 1; i > 0; i--) {
		tmp = pp[0];			/* Extract elements */
		pp[0] = pp[i];
		pp[i] = tmp;
		heapifyports(pp, i, 0);		/* And re-heapify */
	}

	/*
	 * 3. Using a binary search, translate each dependency from a
	 * port directory name into a pointer to a port.
	 */
	for (i = 0; i < pplen; i++)
		translateport(pp, pplen, pp[i]);

	/*
	 * 4. Recursively follow dependencies, expanding the lists of
	 * pointers as needed (using realloc).
	 */
	for (i = 0; i < pplen; i++)
		recurse(pp[i]);

	/*
	 * 5. Iterate through the ports, printing them out (remembering
	 * to list the dependent ports in alphabetical order).
	 */
	for (i = 0; i < pplen; i++)
		printport(pp[i]);

	return 0;
}