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
typedef  int /*<<< orphan*/  tf ;
struct passwd {char* pw_shell; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 char* TKT_ROOT ; 
 scalar_t__ c_flag ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  esetenv (char*,char*,int) ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 int /*<<< orphan*/  getargs ; 
 char* getenv (char*) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ help_flag ; 
 struct passwd* k_getpwuid (scalar_t__) ; 
 scalar_t__ k_hasafs () ; 
 int /*<<< orphan*/  k_setpag () ; 
 scalar_t__ krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* krb5_cc_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* krb5_cc_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_new_unique (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 char** malloc (unsigned int) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  num_args ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  typename_arg ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
    int f;
    char tf[1024];
    char *p;

    char *path;
    char **args;
    unsigned int i;
    int optind = 0;

    setprogname(argv[0]);
    if(getarg(getargs, num_args, argc, argv, &optind))
	usage(1);
    if(help_flag)
	usage(0);
    if(version_flag) {
	print_version(NULL);
	exit(0);
    }

    argc -= optind;
    argv += optind;

#ifdef KRB5
    {
	krb5_error_code ret;
	krb5_context context;
	krb5_ccache id;
	const char *name;

	ret = krb5_init_context(&context);
	if (ret) /* XXX should this really call exit ? */
	    errx(1, "no kerberos 5 support");

	ret = krb5_cc_new_unique(context, typename_arg, NULL, &id);
	if (ret)
	    krb5_err(context, 1, ret, "Failed generating credential cache");

	name = krb5_cc_get_name(context, id);
	if (name == NULL)
	    krb5_errx(context, 1, "Generated credential cache have no name");

	snprintf(tf, sizeof(tf), "%s:%s", krb5_cc_get_type(context, id), name);

	ret = krb5_cc_close(context, id);
	if (ret)
	    krb5_err(context, 1, ret, "Failed closing credential cache");

	krb5_free_context(context);

	esetenv("KRB5CCNAME", tf, 1);
    }
#endif

    snprintf (tf, sizeof(tf), "%s_XXXXXX", TKT_ROOT);
    f = mkstemp (tf);
    if (f < 0)
	err(1, "mkstemp failed");
    close (f);
    unlink (tf);
    esetenv("KRBTKFILE", tf, 1);

    i = 0;

    args = (char **) malloc((argc + 10)*sizeof(char *));
    if (args == NULL)
	errx (1, "Out of memory allocating %lu bytes",
	      (unsigned long)((argc + 10)*sizeof(char *)));

    if(*argv == NULL) {
	path = getenv("SHELL");
	if(path == NULL){
	    struct passwd *pw = k_getpwuid(geteuid());
	    if (pw == NULL)
		errx(1, "no such user: %d", (int)geteuid());
	    path = strdup(pw->pw_shell);
	}
    } else {
	path = strdup(*argv++);
    }
    if (path == NULL)
	errx (1, "Out of memory copying path");

    p=strrchr(path, '/');
    if(p)
	args[i] = strdup(p+1);
    else
	args[i] = strdup(path);

    if (args[i++] == NULL)
	errx (1, "Out of memory copying arguments");

    while(*argv)
	args[i++] = *argv++;

    args[i++] = NULL;

    if(k_hasafs())
	k_setpag();

    unsetenv("PAGPID");
    execvp(path, args);
    if (errno == ENOENT || c_flag) {
	char **sh_args = malloc ((i + 2) * sizeof(char *));
	unsigned int j;

	if (sh_args == NULL)
	    errx (1, "Out of memory copying sh arguments");
	for (j = 1; j < i; ++j)
	    sh_args[j + 2] = args[j];
	sh_args[0] = "sh";
	sh_args[1] = "-c";
	sh_args[2] = path;
	execv ("/bin/sh", sh_args);
    }
    err (1, "execvp");
}