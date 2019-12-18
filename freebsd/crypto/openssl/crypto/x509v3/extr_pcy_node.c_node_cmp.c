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
struct TYPE_6__ {TYPE_1__* data; } ;
typedef  TYPE_2__ X509_POLICY_NODE ;
struct TYPE_5__ {int /*<<< orphan*/  valid_policy; } ;

/* Variables and functions */
 int OBJ_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int node_cmp(const X509_POLICY_NODE *const *a,
                    const X509_POLICY_NODE *const *b)
{
    return OBJ_cmp((*a)->data->valid_policy, (*b)->data->valid_policy);
}