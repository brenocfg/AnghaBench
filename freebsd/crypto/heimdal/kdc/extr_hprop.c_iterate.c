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
struct prop_data {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  HDB ;

/* Variables and functions */
 int /*<<< orphan*/  HDB_F_DECRYPT ; 
#define  HPROP_HEIMDAL 129 
#define  HPROP_MIT_DUMP 128 
 int hdb_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct prop_data*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int,char*) ; 
 int mit_prop_dump (struct prop_data*,char const*) ; 
 int /*<<< orphan*/  v5_prop ; 

__attribute__((used)) static int
iterate (krb5_context context,
	 const char *database_name,
	 HDB *db,
	 int type,
	 struct prop_data *pd)
{
    int ret;

    switch(type) {
    case HPROP_MIT_DUMP:
	ret = mit_prop_dump(pd, database_name);
	if (ret)
	    krb5_warn(context, ret, "mit_prop_dump");
	break;
    case HPROP_HEIMDAL:
	ret = hdb_foreach(context, db, HDB_F_DECRYPT, v5_prop, pd);
	if(ret)
	    krb5_warn(context, ret, "hdb_foreach");
	break;
    default:
	krb5_errx(context, 1, "unknown prop type: %d", type);
    }
    return ret;
}