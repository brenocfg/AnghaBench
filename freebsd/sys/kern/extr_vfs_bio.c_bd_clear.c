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
struct bufdomain {scalar_t__ bd_numdirtybuffers; scalar_t__ bd_lodirtybuffers; scalar_t__ bd_hidirtybuffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_DOMAIN (struct bufdomain*) ; 
 int /*<<< orphan*/  BIT_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUF_DOMAINS ; 
 int /*<<< orphan*/  bdhidirty ; 
 int /*<<< orphan*/  bdirtylock ; 
 int /*<<< orphan*/  bdlodirty ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bd_clear(struct bufdomain *bd)
{

	mtx_lock(&bdirtylock);
	if (bd->bd_numdirtybuffers <= bd->bd_lodirtybuffers)
		BIT_CLR(BUF_DOMAINS, BD_DOMAIN(bd), &bdlodirty);
	if (bd->bd_numdirtybuffers <= bd->bd_hidirtybuffers)
		BIT_CLR(BUF_DOMAINS, BD_DOMAIN(bd), &bdhidirty);
	mtx_unlock(&bdirtylock);
}