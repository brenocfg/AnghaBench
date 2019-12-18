#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/ * krb5_ccache ;
struct TYPE_7__ {scalar_t__ (* hdb_open ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hdb_destroy ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ HDB ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
#define  HPROP_HEIMDAL 129 
#define  HPROP_MIT_DUMP 128 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/ * database ; 
 scalar_t__ decrypt_flag ; 
 int dump_database (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ encrypt_flag ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_creds (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 scalar_t__ hdb_create (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 scalar_t__ hdb_read_master_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ help_flag ; 
 scalar_t__ krb5_allow_weak_crypto (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  krb5_cc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_default_realm (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ local_realm ; 
 int /*<<< orphan*/  mkey5 ; 
 int /*<<< orphan*/  mkeyfile ; 
 int /*<<< orphan*/  num_args ; 
 int parse_source_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int propagate_database (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,int,char**) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/ * source_type ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ to_stdout ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    krb5_context context;
    krb5_ccache ccache = NULL;
    HDB *db = NULL;
    int optidx = 0;

    int type, exit_code;

    setprogname(argv[0]);

    if(getarg(args, num_args, argc, argv, &optidx))
	usage(1);

    if(help_flag)
	usage(0);

    if(version_flag){
	print_version(NULL);
	exit(0);
    }

    ret = krb5_init_context(&context);
    if(ret)
	exit(1);

    /* We may be reading an old database encrypted with a DES master key. */
    ret = krb5_allow_weak_crypto(context, 1);
    if(ret)
        krb5_err(context, 1, ret, "krb5_allow_weak_crypto");

    if(local_realm)
	krb5_set_default_realm(context, local_realm);

    if(encrypt_flag && decrypt_flag)
	krb5_errx(context, 1,
		  "only one of `--encrypt' and `--decrypt' is meaningful");

    if(source_type != NULL) {
	type = parse_source_type(source_type);
	if(type == 0)
	    krb5_errx(context, 1, "unknown source type `%s'", source_type);
    } else
	type = HPROP_HEIMDAL;

    if(!to_stdout)
	get_creds(context, &ccache);

    if(decrypt_flag || encrypt_flag) {
	ret = hdb_read_master_key(context, mkeyfile, &mkey5);
	if(ret && ret != ENOENT)
	    krb5_err(context, 1, ret, "hdb_read_master_key");
	if(ret)
	    krb5_errx(context, 1, "No master key file found");
    }

    switch(type) {
    case HPROP_MIT_DUMP:
	if (database == NULL)
	    krb5_errx(context, 1, "no dump file specified");
	break;
    case HPROP_HEIMDAL:
	ret = hdb_create (context, &db, database);
	if(ret)
	    krb5_err(context, 1, ret, "hdb_create: %s", database);
	ret = db->hdb_open(context, db, O_RDONLY, 0);
	if(ret)
	    krb5_err(context, 1, ret, "db->hdb_open");
	break;
    default:
	krb5_errx(context, 1, "unknown dump type `%d'", type);
	break;
    }

    if (to_stdout)
	exit_code = dump_database (context, type, database, db);
    else
	exit_code = propagate_database (context, type, database,
					db, ccache, optidx, argc, argv);

    if(ccache != NULL)
	krb5_cc_destroy(context, ccache);

    if(db != NULL)
	(*db->hdb_destroy)(context, db);

    krb5_free_context(context);
    return exit_code;
}