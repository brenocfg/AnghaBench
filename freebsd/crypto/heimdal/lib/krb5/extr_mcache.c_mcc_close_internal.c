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
struct TYPE_4__ {scalar_t__ refcnt; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ krb5_mcache ;

/* Variables and functions */
 scalar_t__ MISDEAD (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mcc_close_internal(krb5_mcache *m)
{
    if (--m->refcnt != 0)
	return 0;

    if (MISDEAD(m)) {
	free (m->name);
	return 1;
    }
    return 0;
}