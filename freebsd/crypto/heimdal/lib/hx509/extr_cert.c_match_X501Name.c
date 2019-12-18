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
struct TYPE_6__ {size_t len; int /*<<< orphan*/ * val; } ;
struct TYPE_7__ {TYPE_1__ rdnSequence; } ;
struct TYPE_8__ {scalar_t__ element; TYPE_2__ u; } ;
typedef  TYPE_3__ Name ;

/* Variables and functions */
 int HX509_NAME_CONSTRAINT_ERROR ; 
 scalar_t__ choice_Name_rdnSequence ; 
 int match_RDN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
match_X501Name(const Name *c, const Name *n)
{
    size_t i;
    int ret;

    if (c->element != choice_Name_rdnSequence
	|| n->element != choice_Name_rdnSequence)
	return 0;
    if (c->u.rdnSequence.len > n->u.rdnSequence.len)
	return HX509_NAME_CONSTRAINT_ERROR;
    for (i = 0; i < c->u.rdnSequence.len; i++) {
	ret = match_RDN(&c->u.rdnSequence.val[i], &n->u.rdnSequence.val[i]);
	if (ret)
	    return ret;
    }
    return 0;
}