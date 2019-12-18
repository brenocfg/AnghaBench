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
struct krb5_krbhst_data {int flags; } ;

/* Variables and functions */
 int KD_LARGE_MSG ; 
 int KRB5_KRBHST_TCP ; 
 int KRB5_KRBHST_UDP ; 

__attribute__((used)) static int
krbhst_get_default_proto(struct krb5_krbhst_data *kd)
{
    if (kd->flags & KD_LARGE_MSG)
	return KRB5_KRBHST_TCP;
    return KRB5_KRBHST_UDP;
}