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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int krb5_error_code ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int krb5_storage_to_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static krb5_error_code
write_storage(krb5_context context, krb5_storage *sp, int fd)
{
    krb5_error_code ret;
    krb5_data data;
    ssize_t sret;

    ret = krb5_storage_to_data(sp, &data);
    if (ret) {
	krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	return ret;
    }
    sret = write(fd, data.data, data.length);
    ret = (sret != (ssize_t)data.length);
    krb5_data_free(&data);
    if (ret) {
	ret = errno;
	krb5_set_error_message(context, ret,
			       N_("Failed to write FILE credential data", ""));
	return ret;
    }
    return 0;
}