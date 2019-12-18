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
 int MASK ; 
 char* MINUSKVAR ; 
 int ROTORSZ ; 
 int* deck ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getchar () ; 
 char* getenv (char*) ; 
 char* getpass (char*) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  setup (char*) ; 
 int /*<<< orphan*/  shuffle (int*) ; 
 int /*<<< orphan*/  stderr ; 
 int* t1 ; 
 int* t2 ; 
 int* t3 ; 

int
main(int argc, char *argv[])
{
	int i, n1, n2, nr1, nr2;
	int secureflg = 0, kflag = 0;
	char *cp;

	if (argc > 1 && argv[1][0] == '-') {
		if (argv[1][1] == 's') {
			argc--;
			argv++;
			secureflg = 1;
		} else if (argv[1][1] == 'k') {
			argc--;
			argv++;
			kflag = 1;
		}
	}
	if (kflag) {
		if ((cp = getenv(MINUSKVAR)) == NULL) {
			fprintf(stderr, "%s not set\n", MINUSKVAR);
			exit(1);
		}
		setup(cp);
	} else if (argc != 2) {
		setup(getpass("Enter key:"));
	}
	else
		setup(argv[1]);
	n1 = 0;
	n2 = 0;
	nr2 = 0;

	while((i=getchar()) != -1) {
		if (secureflg) {
			nr1 = deck[n1]&MASK;
			nr2 = deck[nr1]&MASK;
		} else {
			nr1 = n1;
		}
		i = t2[(t3[(t1[(i+nr1)&MASK]+nr2)&MASK]-nr2)&MASK]-nr1;
		putchar(i);
		n1++;
		if(n1==ROTORSZ) {
			n1 = 0;
			n2++;
			if(n2==ROTORSZ) n2 = 0;
			if (secureflg) {
				shuffle(deck);
			} else {
				nr2 = n2;
			}
		}
	}

	return 0;
}