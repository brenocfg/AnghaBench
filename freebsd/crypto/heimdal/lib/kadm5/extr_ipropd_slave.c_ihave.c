#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int krb5_error_code ;
struct TYPE_3__ {int length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_auth_context ;

/* Variables and functions */
 int /*<<< orphan*/  I_HAVE ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_mem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int,char*) ; 
 int krb5_write_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_1__*) ; 

__attribute__((used)) static krb5_error_code
ihave (krb5_context context, krb5_auth_context auth_context,
       int fd, uint32_t version)
{
    int ret;
    u_char buf[8];
    krb5_storage *sp;
    krb5_data data;

    sp = krb5_storage_from_mem (buf, 8);
    krb5_store_int32 (sp, I_HAVE);
    krb5_store_int32 (sp, version);
    krb5_storage_free (sp);
    data.length = 8;
    data.data   = buf;

    ret = krb5_write_priv_message(context, auth_context, &fd, &data);
    if (ret)
	krb5_warn (context, ret, "krb5_write_message");
    return ret;
}