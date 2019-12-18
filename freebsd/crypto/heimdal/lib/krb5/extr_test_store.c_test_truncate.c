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
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_storage_truncate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  krb5_store_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
test_truncate(krb5_context context, krb5_storage *sp, int fd)
{
    struct stat sb;

    krb5_store_string(sp, "hej");
    krb5_storage_truncate(sp, 2);

    if (fstat(fd, &sb) != 0)
	krb5_err(context, 1, errno, "fstat");
    if (sb.st_size != 2)
	krb5_errx(context, 1, "length not 2");

    krb5_storage_truncate(sp, 1024);

    if (fstat(fd, &sb) != 0)
	krb5_err(context, 1, errno, "fstat");
    if (sb.st_size != 1024)
	krb5_errx(context, 1, "length not 2");
}