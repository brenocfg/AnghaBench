#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dump_options {scalar_t__ decrypt_flag; } ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_6__ {int /*<<< orphan*/  (* hdb_close ) (int /*<<< orphan*/ ,TYPE_1__*) ;scalar_t__ (* hdb_open ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ HDB ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  HDB_F_DECRYPT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 TYPE_1__* _kadm5_s_get_db (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  hdb_foreach (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdb_print_entry ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  local_flag ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 

int
dump(struct dump_options *opt, int argc, char **argv)
{
    krb5_error_code ret;
    FILE *f;
    HDB *db = NULL;

    if(!local_flag) {
	krb5_warnx(context, "dump is only available in local (-l) mode");
	return 0;
    }

    db = _kadm5_s_get_db(kadm_handle);

    if(argc == 0)
	f = stdout;
    else
	f = fopen(argv[0], "w");

    if(f == NULL) {
	krb5_warn(context, errno, "open: %s", argv[0]);
	goto out;
    }
    ret = db->hdb_open(context, db, O_RDONLY, 0600);
    if(ret) {
	krb5_warn(context, ret, "hdb_open");
	goto out;
    }

    hdb_foreach(context, db, opt->decrypt_flag ? HDB_F_DECRYPT : 0,
		hdb_print_entry, f);

    db->hdb_close(context, db);
out:
    if(f && f != stdout)
	fclose(f);
    return 0;
}