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
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dten_vstate; } ;
typedef  TYPE_1__ dtrace_enabling_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dtrace_enabling_t *
dtrace_enabling_create(dtrace_vstate_t *vstate)
{
	dtrace_enabling_t *enab;

	enab = kmem_zalloc(sizeof (dtrace_enabling_t), KM_SLEEP);
	enab->dten_vstate = vstate;

	return (enab);
}