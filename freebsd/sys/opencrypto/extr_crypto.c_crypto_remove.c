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
struct cryptocap {scalar_t__ cc_sessions; scalar_t__ cc_koperations; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  bzero (struct cryptocap*,int) ; 
 int /*<<< orphan*/  crypto_drivers_mtx ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
crypto_remove(struct cryptocap *cap)
{

	mtx_assert(&crypto_drivers_mtx, MA_OWNED);
	if (cap->cc_sessions == 0 && cap->cc_koperations == 0)
		bzero(cap, sizeof(*cap));
}