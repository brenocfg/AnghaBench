#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cell_list {int /*<<< orphan*/ * cell; struct cell_list* next; } ;
typedef  int /*<<< orphan*/  krb5_principal ;
struct TYPE_4__ {int num_strings; char** strings; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afslog_cell (char*,int) ; 
 int /*<<< orphan*/  afslog_file (char*) ; 
 int /*<<< orphan*/  args ; 
 scalar_t__ cache_string ; 
 struct cell_list* cell_list ; 
 TYPE_1__ cells ; 
 scalar_t__ client_string ; 
 int /*<<< orphan*/ * context ; 
 scalar_t__ do_afslog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_1__ files ; 
 int /*<<< orphan*/  free_getarg_strings (TYPE_1__*) ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 scalar_t__ help_flag ; 
 int /*<<< orphan*/ * id ; 
 int /*<<< orphan*/  k_hasafs () ; 
 int /*<<< orphan*/  k_unlog () ; 
 int /*<<< orphan*/  kafs_set_verbose (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_cc_cache_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_cc_default (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_cc_resolve (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int krb5_init_context (int /*<<< orphan*/ **) ; 
 int krb5_parse_name (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  log_func ; 
 int /*<<< orphan*/  num_args ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ unlog_flag ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ verbose ; 
 scalar_t__ version_flag ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ *) ; 

int
main(int argc, char **argv)
{
    int optind = 0;
    int i;
    int num;
    int ret = 0;
    int failed = 0;
    struct cell_list *p;

    setprogname(argv[0]);

    if(getarg(args, num_args, argc, argv, &optind))
	usage(1);
    if(help_flag)
	usage(0);
    if(version_flag) {
	print_version(NULL);
	exit(0);
    }

    if(!k_hasafs())
	errx(1, "AFS does not seem to be present on this machine");

    if(unlog_flag){
	k_unlog();
	exit(0);
    }
#ifdef KRB5
    ret = krb5_init_context(&context);
    if (ret) {
	context = NULL;
    } else {
	if (client_string) {
	    krb5_principal client;

	    ret = krb5_parse_name(context, client_string, &client);
	    if (ret == 0)
		ret = krb5_cc_cache_match(context, client, &id);
	    if (ret)
		id = NULL;
	}
	if (id == NULL && cache_string) {
	    if(krb5_cc_resolve(context, cache_string, &id) != 0) {
		krb5_warnx(context, "failed to open kerberos 5 cache '%s'",
			   cache_string);
		id = NULL;
	    }
	}
	if (id == NULL)
	    if(krb5_cc_default(context, &id) != 0)
		id = NULL;
    }
#endif

    if (verbose)
	kafs_set_verbose(log_func, NULL);

    num = 0;
    for(i = 0; i < files.num_strings; i++){
	afslog_file(files.strings[i]);
	num++;
    }
    free_getarg_strings (&files);
    for(i = 0; i < cells.num_strings; i++){
	afslog_cell(cells.strings[i], 1);
	num++;
    }
    free_getarg_strings (&cells);
    for(i = optind; i < argc; i++){
	num++;
	if(strcmp(argv[i], ".") == 0 ||
	   strcmp(argv[i], "..") == 0 ||
	   strchr(argv[i], '/') ||
	   access(argv[i], F_OK) == 0)
	    afslog_file(argv[i]);
	else
	    afslog_cell(argv[i], 1);
    }
    if(num == 0) {
	if(do_afslog(NULL))
	    failed++;
    } else
	for(p = cell_list; p; p = p->next) {
	    if(verbose)
		warnx("Getting tokens for cell \"%s\"", p->cell);
	    if(do_afslog(p->cell))
		failed++;
    }

    return failed;
}