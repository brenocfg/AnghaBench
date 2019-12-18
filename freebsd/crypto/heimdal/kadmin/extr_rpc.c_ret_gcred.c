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
struct gcred {int /*<<< orphan*/  handle; int /*<<< orphan*/  service; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  proc; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_ret_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct gcred*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ret_data_xdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ret_gcred(krb5_data *data, struct gcred *gcred)
{
    krb5_storage *sp;

    memset(gcred, 0, sizeof(*gcred));

    sp = krb5_storage_from_data(data);
    INSIST(sp != NULL);

    CHECK(krb5_ret_uint32(sp, &gcred->version));
    CHECK(krb5_ret_uint32(sp, &gcred->proc));
    CHECK(krb5_ret_uint32(sp, &gcred->seq_num));
    CHECK(krb5_ret_uint32(sp, &gcred->service));
    CHECK(ret_data_xdr(sp, &gcred->handle));

    krb5_storage_free(sp);

    return 0;
}