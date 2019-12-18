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
struct TYPE_4__ {int /*<<< orphan*/ * key_oid; } ;
typedef  TYPE_1__ hx509_private_key_ops ;
typedef  int /*<<< orphan*/  heim_oid ;

/* Variables and functions */
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_1__** private_algs ; 

hx509_private_key_ops *
hx509_find_private_alg(const heim_oid *oid)
{
    int i;
    for (i = 0; private_algs[i]; i++) {
	if (private_algs[i]->key_oid == NULL)
	    continue;
	if (der_heim_oid_cmp(private_algs[i]->key_oid, oid) == 0)
	    return private_algs[i];
    }
    return NULL;
}