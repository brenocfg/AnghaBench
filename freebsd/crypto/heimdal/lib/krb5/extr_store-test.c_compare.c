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
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_4__ {size_t length; void* data; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_storage_to_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ memcmp (void*,void*,size_t) ; 
 int /*<<< orphan*/  print_data (void*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
compare(const char *name, krb5_storage *sp, void *expected, size_t len)
{
    int ret = 0;
    krb5_data data;
    if (krb5_storage_to_data(sp, &data))
	errx(1, "krb5_storage_to_data failed");
    krb5_storage_free(sp);
    if(data.length != len || memcmp(data.data, expected, len) != 0) {
	printf("%s mismatch\n", name);
	printf("  Expected: ");
	print_data(expected, len);
	printf("  Actual:   ");
	print_data(data.data, data.length);
	ret++;
    }
    krb5_data_free(&data);
    return ret;
}