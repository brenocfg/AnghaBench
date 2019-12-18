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
struct krb5_krbhst_data {int /*<<< orphan*/  hosts; int /*<<< orphan*/ * index; } ;
typedef  int krb5_boolean ;

/* Variables and functions */

__attribute__((used)) static krb5_boolean
krbhst_empty(const struct krb5_krbhst_data *kd)
{
    return kd->index == &kd->hosts;
}