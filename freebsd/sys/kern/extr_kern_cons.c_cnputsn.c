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

/* Variables and functions */
 int /*<<< orphan*/  cnputc (char const) ; 
 int /*<<< orphan*/  cnputs_mtx ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 scalar_t__ use_cnputs_mtx ; 

void
cnputsn(const char *p, size_t n)
{
	size_t i;
	int unlock_reqd = 0;

	if (use_cnputs_mtx) {
	  	/*
		 * NOTE: Debug prints and/or witness printouts in
		 * console driver clients can cause the "cnputs_mtx"
		 * mutex to recurse. Simply return if that happens.
		 */
		if (mtx_owned(&cnputs_mtx))
			return;
		mtx_lock_spin(&cnputs_mtx);
		unlock_reqd = 1;
	}

	for (i = 0; i < n; i++)
		cnputc(p[i]);

	if (unlock_reqd)
		mtx_unlock_spin(&cnputs_mtx);
}