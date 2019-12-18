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

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int) ; 
 int /*<<< orphan*/  krb5_storage_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

krb5_storage *
kadm5_log_goto_end (int fd)
{
    krb5_storage *sp;

    sp = krb5_storage_from_fd (fd);
    krb5_storage_seek(sp, 0, SEEK_END);
    return sp;
}