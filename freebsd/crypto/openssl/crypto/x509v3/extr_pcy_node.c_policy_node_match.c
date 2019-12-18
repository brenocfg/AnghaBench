#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* data; } ;
typedef  TYPE_1__ X509_POLICY_NODE ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_2__ X509_POLICY_LEVEL ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  expected_policy_set; int /*<<< orphan*/ * valid_policy; } ;
typedef  TYPE_3__ X509_POLICY_DATA ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int POLICY_DATA_FLAG_MAP_MASK ; 
 int X509_V_FLAG_INHIBIT_MAP ; 
 int sk_ASN1_OBJECT_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_ASN1_OBJECT_value (int /*<<< orphan*/ ,int) ; 

int policy_node_match(const X509_POLICY_LEVEL *lvl,
                      const X509_POLICY_NODE *node, const ASN1_OBJECT *oid)
{
    int i;
    ASN1_OBJECT *policy_oid;
    const X509_POLICY_DATA *x = node->data;

    if ((lvl->flags & X509_V_FLAG_INHIBIT_MAP)
        || !(x->flags & POLICY_DATA_FLAG_MAP_MASK)) {
        if (!OBJ_cmp(x->valid_policy, oid))
            return 1;
        return 0;
    }

    for (i = 0; i < sk_ASN1_OBJECT_num(x->expected_policy_set); i++) {
        policy_oid = sk_ASN1_OBJECT_value(x->expected_policy_set, i);
        if (!OBJ_cmp(policy_oid, oid))
            return 1;
    }
    return 0;

}