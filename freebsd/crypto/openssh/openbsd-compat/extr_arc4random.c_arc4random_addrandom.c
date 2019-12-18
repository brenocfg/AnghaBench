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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 scalar_t__ IVSZ ; 
 scalar_t__ KEYSZ ; 
 int MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  _ARC4_LOCK () ; 
 int /*<<< orphan*/  _ARC4_UNLOCK () ; 
 int /*<<< orphan*/  _rs_rekey (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _rs_stir () ; 
 int /*<<< orphan*/  rs_initialized ; 

void
arc4random_addrandom(u_char *dat, int datlen)
{
	int m;

	_ARC4_LOCK();
	if (!rs_initialized)
		_rs_stir();
	while (datlen > 0) {
		m = MIN(datlen, KEYSZ + IVSZ);
		_rs_rekey(dat, m);
		dat += m;
		datlen -= m;
	}
	_ARC4_UNLOCK();
}