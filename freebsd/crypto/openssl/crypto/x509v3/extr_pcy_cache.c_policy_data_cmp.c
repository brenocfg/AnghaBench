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
struct TYPE_4__ {int /*<<< orphan*/  valid_policy; } ;
typedef  TYPE_1__ X509_POLICY_DATA ;

/* Variables and functions */
 int OBJ_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int policy_data_cmp(const X509_POLICY_DATA *const *a,
                           const X509_POLICY_DATA *const *b)
{
    return OBJ_cmp((*a)->valid_policy, (*b)->valid_policy);
}