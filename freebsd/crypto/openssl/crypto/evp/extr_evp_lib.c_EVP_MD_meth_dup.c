#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pkey_type; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ EVP_MD ;

/* Variables and functions */
 TYPE_1__* EVP_MD_meth_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

EVP_MD *EVP_MD_meth_dup(const EVP_MD *md)
{
    EVP_MD *to = EVP_MD_meth_new(md->type, md->pkey_type);

    if (to != NULL)
        memcpy(to, md, sizeof(*to));
    return to;
}