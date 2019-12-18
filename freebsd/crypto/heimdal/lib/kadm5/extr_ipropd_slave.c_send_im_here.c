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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_auth_context ;

/* Variables and functions */
 int /*<<< orphan*/  I_AM_HERE ; 
 int krb5_data_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  krb5_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int krb5_write_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
send_im_here (krb5_context context, int fd,
	      krb5_auth_context auth_context)
{
    krb5_storage *sp;
    krb5_data data;
    int ret;

    ret = krb5_data_alloc (&data, 4);
    if (ret)
	krb5_err (context, 1, ret, "send_im_here");

    sp = krb5_storage_from_data (&data);
    if (sp == NULL)
	krb5_errx (context, 1, "krb5_storage_from_data");
    krb5_store_int32(sp, I_AM_HERE);
    krb5_storage_free(sp);

    ret = krb5_write_priv_message(context, auth_context, &fd, &data);
    krb5_data_free(&data);

    if (ret)
	krb5_err (context, 1, ret, "krb5_write_priv_message");
}