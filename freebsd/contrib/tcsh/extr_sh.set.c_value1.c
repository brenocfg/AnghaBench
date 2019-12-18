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
struct varent {int /*<<< orphan*/ ** vec; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/ * STRNULL ; 
 struct varent* adrof1 (int /*<<< orphan*/ *,struct varent*) ; 

Char   *
value1(Char *var, struct varent *head)
{
    struct varent *vp;

    if (!var || !head)		/* PWP: extra error checking */
	return (STRNULL);

    vp = adrof1(var, head);
    return ((vp == NULL || vp->vec == NULL || vp->vec[0] == NULL) ?
	STRNULL : vp->vec[0]);
}