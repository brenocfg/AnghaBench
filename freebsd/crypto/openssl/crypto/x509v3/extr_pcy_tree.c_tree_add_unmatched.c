#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_POLICY_TREE ;
struct TYPE_15__ {TYPE_1__* data; } ;
typedef  TYPE_3__ X509_POLICY_NODE ;
typedef  int /*<<< orphan*/  X509_POLICY_LEVEL ;
struct TYPE_16__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  qualifier_set; } ;
typedef  TYPE_4__ X509_POLICY_DATA ;
struct TYPE_17__ {TYPE_2__* anyPolicy; } ;
typedef  TYPE_5__ X509_POLICY_CACHE ;
struct TYPE_14__ {int /*<<< orphan*/  qualifier_set; } ;
struct TYPE_13__ {int /*<<< orphan*/ * valid_policy; } ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  POLICY_DATA_FLAG_SHARED_QUALIFIERS ; 
 int /*<<< orphan*/ * level_add_node (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_critical (TYPE_3__*) ; 
 int /*<<< orphan*/  policy_data_free (TYPE_4__*) ; 
 TYPE_4__* policy_data_new (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tree_add_unmatched(X509_POLICY_LEVEL *curr,
                              const X509_POLICY_CACHE *cache,
                              const ASN1_OBJECT *id,
                              X509_POLICY_NODE *node, X509_POLICY_TREE *tree)
{
    X509_POLICY_DATA *data;

    if (id == NULL)
        id = node->data->valid_policy;
    /*
     * Create a new node with qualifiers from anyPolicy and id from unmatched
     * node.
     */
    if ((data = policy_data_new(NULL, id, node_critical(node))) == NULL)
        return 0;

    /* Curr may not have anyPolicy */
    data->qualifier_set = cache->anyPolicy->qualifier_set;
    data->flags |= POLICY_DATA_FLAG_SHARED_QUALIFIERS;
    if (level_add_node(curr, data, node, tree) == NULL) {
        policy_data_free(data);
        return 0;
    }
    return 1;
}