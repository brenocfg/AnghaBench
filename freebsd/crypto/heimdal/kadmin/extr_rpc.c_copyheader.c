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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_error_code ;
struct TYPE_4__ {size_t length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  krb5_data_alloc (TYPE_1__*,scalar_t__) ; 
 scalar_t__ krb5_storage_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ krb5_storage_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
copyheader(krb5_storage *sp, krb5_data *data)
{
    off_t off;
    ssize_t sret;

    off = krb5_storage_seek(sp, 0, SEEK_CUR);

    CHECK(krb5_data_alloc(data, off));
    INSIST((size_t)off == data->length);
    krb5_storage_seek(sp, 0, SEEK_SET);
    sret = krb5_storage_read(sp, data->data, data->length);
    INSIST(sret == off);
    INSIST(off == krb5_storage_seek(sp, 0, SEEK_CUR));

    return 0;
}