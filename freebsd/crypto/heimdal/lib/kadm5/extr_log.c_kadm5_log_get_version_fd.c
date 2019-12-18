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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  krb5_ret_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int) ; 
 int /*<<< orphan*/  krb5_storage_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kadm5_ret_t
kadm5_log_get_version_fd (int fd,
			  uint32_t *ver)
{
    int ret;
    krb5_storage *sp;
    int32_t old_version;

    ret = lseek (fd, 0, SEEK_END);
    if(ret < 0)
	return errno;
    if(ret == 0) {
	*ver = 0;
	return 0;
    }
    sp = krb5_storage_from_fd (fd);
    krb5_storage_seek(sp, -4, SEEK_CUR);
    krb5_ret_int32 (sp, &old_version);
    *ver = old_version;
    krb5_storage_free(sp);
    lseek (fd, 0, SEEK_END);
    return 0;
}