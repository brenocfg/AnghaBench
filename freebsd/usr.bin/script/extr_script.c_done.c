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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ fflg ; 
 char* fmfname ; 
 char* fname ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fscript ; 
 int /*<<< orphan*/  master ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  qflg ; 
 scalar_t__ rawout ; 
 int /*<<< orphan*/  record (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 
 scalar_t__ showexit ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tt ; 
 scalar_t__ ttyflg ; 

__attribute__((used)) static void
done(int eno)
{
	time_t tvec;

	if (ttyflg)
		(void)tcsetattr(STDIN_FILENO, TCSAFLUSH, &tt);
	tvec = time(NULL);
	if (rawout)
		record(fscript, NULL, 0, 'e');
	if (!qflg) {
		if (!rawout) {
			if (showexit)
				(void)fprintf(fscript, "\nCommand exit status:"
				    " %d", eno);
			(void)fprintf(fscript,"\nScript done on %s",
			    ctime(&tvec));
		}
		(void)printf("\nScript done, output file is %s\n", fname);
		if (fflg) {
			(void)printf("Filemon done, output file is %s\n",
			    fmfname);
		}
	}
	(void)fclose(fscript);
	(void)close(master);
	exit(eno);
}