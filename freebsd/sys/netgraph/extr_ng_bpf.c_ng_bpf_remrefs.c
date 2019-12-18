#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * hook_p ;
typedef  TYPE_1__* hinfo_p ;
struct TYPE_3__ {int /*<<< orphan*/ * nomatch; int /*<<< orphan*/ * match; } ;

/* Variables and functions */
 TYPE_1__* NG_HOOK_PRIVATE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_bpf_remrefs(hook_p hook, void* arg)
{
	hinfo_p hip = NG_HOOK_PRIVATE(hook);
	hook_p h = (hook_p)arg;

	if (hip->match == h)
	    hip->match = NULL;
	if (hip->nomatch == h)
	    hip->nomatch = NULL;
	return (1);
}