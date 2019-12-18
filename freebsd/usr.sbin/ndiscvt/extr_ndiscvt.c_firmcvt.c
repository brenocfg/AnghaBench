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
typedef  int /*<<< orphan*/  sysbuf ;

/* Variables and functions */
 char* basename (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 char tolower (char) ; 

__attribute__((used)) static void
firmcvt(char *firmfile)
{
	char			*basefile, *outfile, *ptr;
	char			sysbuf[1024];

	outfile = strdup(basename(firmfile));
	basefile = strdup(outfile);

	snprintf(sysbuf, sizeof(sysbuf),
#ifdef __i386__
	    "objcopy -I binary -O elf32-i386-freebsd -B i386 %s %s.o\n",
#endif
#ifdef __amd64__
	    "objcopy -I binary -O elf64-x86-64-freebsd -B i386 %s %s.o\n",
#endif
	    firmfile, outfile);
	printf("%s", sysbuf);
	system(sysbuf);

	ptr = firmfile;
	while (*ptr) {
		if (*ptr == '/' || *ptr == '.')
			*ptr = '_';
		ptr++;
	}
	ptr = basefile;
	while (*ptr) {
		if (*ptr == '/' || *ptr == '.')
			*ptr = '_';
		else
			*ptr = tolower(*ptr);
		ptr++;
	}

	snprintf(sysbuf, sizeof(sysbuf),
	    "objcopy --redefine-sym _binary_%s_start=%s_start "
	    "--strip-symbol _binary_%s_size "
	    "--redefine-sym _binary_%s_end=%s_end %s.o %s.o\n",
	    firmfile, basefile, firmfile, firmfile,
	    basefile, outfile, outfile);
	ptr = sysbuf;
	printf("%s", sysbuf);
	system(sysbuf);

	snprintf(sysbuf, sizeof(sysbuf),
	    "ld -Bshareable -d -warn-common -o %s.ko %s.o\n",
	    outfile, outfile);
	printf("%s", sysbuf);
	system(sysbuf);

	free(basefile);

	exit(0);
}