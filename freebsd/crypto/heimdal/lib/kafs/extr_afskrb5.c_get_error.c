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
struct krb5_kafs_data {int /*<<< orphan*/  context; } ;
struct kafs_data {struct krb5_kafs_data* data; } ;

/* Variables and functions */
 char const* krb5_get_error_message (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const char *
get_error(struct kafs_data *data, int error)
{
    struct krb5_kafs_data *d = data->data;
    return krb5_get_error_message(d->context, error);
}