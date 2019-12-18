#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  ac; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ slave ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int krb5_error_code ;
struct TYPE_15__ {char* data; int length; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_16__ {int (* hdb_open ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hdb_destroy ) (int /*<<< orphan*/ ,TYPE_3__*) ;int /*<<< orphan*/  (* hdb_close ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
typedef  TYPE_3__ HDB ;

/* Variables and functions */
 int /*<<< orphan*/  HDB_F_ADMIN_DATA ; 
 int /*<<< orphan*/  NOW_YOU_HAVE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TELL_YOU_EVERYTHING ; 
 int hdb_create (int /*<<< orphan*/ ,TYPE_3__**,char const*) ; 
 int hdb_foreach (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_mem (char*,int) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int,char*) ; 
 int krb5_write_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  prop_one ; 
 int /*<<< orphan*/  slave_dead (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  slave_seen (TYPE_1__*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int
send_complete (krb5_context context, slave *s,
	       const char *database, uint32_t current_version)
{
    krb5_error_code ret;
    krb5_storage *sp;
    HDB *db;
    krb5_data data;
    char buf[8];

    ret = hdb_create (context, &db, database);
    if (ret)
	krb5_err (context, 1, ret, "hdb_create: %s", database);
    ret = db->hdb_open (context, db, O_RDONLY, 0);
    if (ret)
	krb5_err (context, 1, ret, "db->open");

    sp = krb5_storage_from_mem (buf, 4);
    if (sp == NULL)
	krb5_errx (context, 1, "krb5_storage_from_mem");
    krb5_store_int32 (sp, TELL_YOU_EVERYTHING);
    krb5_storage_free (sp);

    data.data   = buf;
    data.length = 4;

    ret = krb5_write_priv_message(context, s->ac, &s->fd, &data);

    if (ret) {
	krb5_warn (context, ret, "krb5_write_priv_message");
	slave_dead(context, s);
	return ret;
    }

    ret = hdb_foreach (context, db, HDB_F_ADMIN_DATA, prop_one, s);
    if (ret) {
	krb5_warn (context, ret, "hdb_foreach");
	slave_dead(context, s);
	return ret;
    }

    (*db->hdb_close)(context, db);
    (*db->hdb_destroy)(context, db);

    sp = krb5_storage_from_mem (buf, 8);
    if (sp == NULL)
	krb5_errx (context, 1, "krb5_storage_from_mem");
    krb5_store_int32 (sp, NOW_YOU_HAVE);
    krb5_store_int32 (sp, current_version);
    krb5_storage_free (sp);

    data.length = 8;

    s->version = current_version;

    ret = krb5_write_priv_message(context, s->ac, &s->fd, &data);
    if (ret) {
	slave_dead(context, s);
	krb5_warn (context, ret, "krb5_write_priv_message");
	return ret;
    }

    slave_seen(s);

    return 0;
}