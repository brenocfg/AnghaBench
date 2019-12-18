#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct foreach_data {scalar_t__ exp2; scalar_t__ exp; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {int /*<<< orphan*/  principal; } ;
struct TYPE_5__ {TYPE_1__ entry; } ;
typedef  TYPE_2__ hdb_entry_ex ;
typedef  int /*<<< orphan*/  HDB ;

/* Variables and functions */
 scalar_t__ add_princ (struct foreach_data*,char*) ; 
 scalar_t__ fnmatch (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static krb5_error_code
foreach(krb5_context context, HDB *db, hdb_entry_ex *ent, void *data)
{
    struct foreach_data *d = data;
    char *princ;
    krb5_error_code ret;
    ret = krb5_unparse_name(context, ent->entry.principal, &princ);
    if(ret)
	return ret;
    if(d->exp){
	if(fnmatch(d->exp, princ, 0) == 0 || fnmatch(d->exp2, princ, 0) == 0)
	    ret = add_princ(d, princ);
	else
	    free(princ);
    }else{
	ret = add_princ(d, princ);
    }
    if(ret)
	free(princ);
    return ret;
}