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
typedef  int /*<<< orphan*/  timestr ;
typedef  int /*<<< orphan*/  time_t ;
struct getargs {int short_name; char* long_name; scalar_t__ type; char* help; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ISFLAG (struct getargs) ; 
 scalar_t__ arg_negative_flag ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_arg (char*,int,int,int,struct getargs*,char* (*) (char const*)) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  strupr (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mandoc_template(struct getargs *args,
		size_t num_args,
		const char *progname,
		const char *extra_string,
		char *(i18n)(const char *))
{
    size_t i;
    char timestr[64], cmd[64];
    char buf[128];
    const char *p;
    time_t t;

    printf(".\\\" Things to fix:\n");
    printf(".\\\"   * correct section, and operating system\n");
    printf(".\\\"   * remove Op from mandatory flags\n");
    printf(".\\\"   * use better macros for arguments (like .Pa for files)\n");
    printf(".\\\"\n");
    t = time(NULL);
    strftime(timestr, sizeof(timestr), "%B %e, %Y", localtime(&t));
    printf(".Dd %s\n", timestr);
    p = strrchr(progname, '/');
    if(p) p++; else p = progname;
    strlcpy(cmd, p, sizeof(cmd));
    strupr(cmd);

    printf(".Dt %s SECTION\n", cmd);
    printf(".Os OPERATING_SYSTEM\n");
    printf(".Sh NAME\n");
    printf(".Nm %s\n", p);
    printf(".Nd in search of a description\n");
    printf(".Sh SYNOPSIS\n");
    printf(".Nm\n");
    for(i = 0; i < num_args; i++){
	/* we seem to hit a limit on number of arguments if doing
           short and long flags with arguments -- split on two lines */
	if(ISFLAG(args[i]) ||
	   args[i].short_name == 0 || args[i].long_name == NULL) {
	    printf(".Op ");

	    if(args[i].short_name) {
		print_arg(buf, sizeof(buf), 1, 0, args + i, i18n);
		printf("Fl %c%s", args[i].short_name, buf);
		if(args[i].long_name)
		    printf(" | ");
	    }
	    if(args[i].long_name) {
		print_arg(buf, sizeof(buf), 1, 1, args + i, i18n);
		printf("Fl Fl %s%s%s",
		       args[i].type == arg_negative_flag ? "no-" : "",
		       args[i].long_name, buf);
	    }
	    printf("\n");
	} else {
	    print_arg(buf, sizeof(buf), 1, 0, args + i, i18n);
	    printf(".Oo Fl %c%s \\*(Ba Xo\n", args[i].short_name, buf);
	    print_arg(buf, sizeof(buf), 1, 1, args + i, i18n);
	    printf(".Fl Fl %s%s\n.Xc\n.Oc\n", args[i].long_name, buf);
	}
    /*
	    if(args[i].type == arg_strings)
		fprintf (stderr, "...");
		*/
    }
    if (extra_string && *extra_string)
	printf (".Ar %s\n", extra_string);
    printf(".Sh DESCRIPTION\n");
    printf("Supported options:\n");
    printf(".Bl -tag -width Ds\n");
    for(i = 0; i < num_args; i++){
	printf(".It Xo\n");
	if(args[i].short_name){
	    printf(".Fl %c", args[i].short_name);
	    print_arg(buf, sizeof(buf), 1, 0, args + i, i18n);
	    printf("%s", buf);
	    if(args[i].long_name)
		printf(" ,");
	    printf("\n");
	}
	if(args[i].long_name){
	    printf(".Fl Fl %s%s",
		   args[i].type == arg_negative_flag ? "no-" : "",
		   args[i].long_name);
	    print_arg(buf, sizeof(buf), 1, 1, args + i, i18n);
	    printf("%s\n", buf);
	}
	printf(".Xc\n");
	if(args[i].help)
	    printf("%s\n", args[i].help);
    /*
	    if(args[i].type == arg_strings)
		fprintf (stderr, "...");
		*/
    }
    printf(".El\n");
    printf(".\\\".Sh ENVIRONMENT\n");
    printf(".\\\".Sh FILES\n");
    printf(".\\\".Sh EXAMPLES\n");
    printf(".\\\".Sh DIAGNOSTICS\n");
    printf(".\\\".Sh SEE ALSO\n");
    printf(".\\\".Sh STANDARDS\n");
    printf(".\\\".Sh HISTORY\n");
    printf(".\\\".Sh AUTHORS\n");
    printf(".\\\".Sh BUGS\n");
}