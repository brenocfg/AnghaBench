#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* krb5_krbhst_handle ;
struct TYPE_3__ {char const* realm; } ;

/* Variables and functions */

const char *
_krb5_krbhst_get_realm(krb5_krbhst_handle handle)
{
    return handle->realm;
}