#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tl_data_contents; int /*<<< orphan*/  tl_data_length; int /*<<< orphan*/  tl_data_type; } ;
typedef  TYPE_1__ krb5_tl_data ;
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_store_data (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kadm5_ret_t
kadm5_store_tl_data(krb5_storage *sp,
		    krb5_tl_data *tl)
{
    krb5_data c;
    krb5_store_int32(sp, tl->tl_data_type);
    c.length = tl->tl_data_length;
    c.data = tl->tl_data_contents;
    krb5_store_data(sp, c);
    return 0;
}