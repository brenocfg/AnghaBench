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
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 char const* bakfile ; 
 int /*<<< orphan*/  close (int) ; 
 int creat (char const*,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 void* fopen (char const*,char*) ; 
 char const* in_name ; 
 int /*<<< orphan*/ * input ; 
 int /*<<< orphan*/ * output ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  simple_backup_suffix ; 
 int /*<<< orphan*/  sprintf (char const*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
bakcopy(void)
{
    int         n,
                bakchn;
    char        buff[8 * 1024];
    const char *p;

    /* construct file name .Bfile */
    for (p = in_name; *p; p++);	/* skip to end of string */
    while (p > in_name && *p != '/')	/* find last '/' */
	p--;
    if (*p == '/')
	p++;
    sprintf(bakfile, "%s%s", p, simple_backup_suffix);

    /* copy in_name to backup file */
    bakchn = creat(bakfile, 0600);
    if (bakchn < 0)
	err(1, "%s", bakfile);
    while ((n = read(fileno(input), buff, sizeof(buff))) > 0)
	if (write(bakchn, buff, n) != n)
	    err(1, "%s", bakfile);
    if (n < 0)
	err(1, "%s", in_name);
    close(bakchn);
    fclose(input);

    /* re-open backup file as the input file */
    input = fopen(bakfile, "r");
    if (input == NULL)
	err(1, "%s", bakfile);
    /* now the original input file will be the output */
    output = fopen(in_name, "w");
    if (output == NULL) {
	unlink(bakfile);
	err(1, "%s", in_name);
    }
}