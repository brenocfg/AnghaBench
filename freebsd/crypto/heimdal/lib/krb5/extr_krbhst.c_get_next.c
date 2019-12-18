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
struct krb5_krbhst_info {struct krb5_krbhst_info* next; } ;
struct krb5_krbhst_data {struct krb5_krbhst_info** index; } ;
typedef  struct krb5_krbhst_info krb5_krbhst_info ;
typedef  int /*<<< orphan*/  krb5_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static krb5_boolean
get_next(struct krb5_krbhst_data *kd, krb5_krbhst_info **host)
{
    struct krb5_krbhst_info *hi = *kd->index;
    if(hi != NULL) {
	*host = hi;
	kd->index = &(*kd->index)->next;
	return TRUE;
    }
    return FALSE;
}