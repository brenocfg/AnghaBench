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
typedef  scalar_t__ u_int16_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  scalar_t__ u_char ;
struct timeval {int tv_sec; int tv_usec; } ;
typedef  TYPE_1__* res_state ;
struct TYPE_3__ {scalar_t__* _rnd; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  MD5_Final (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__* srnd ; 

u_int
res_nrandomid(res_state statp) {
	struct timeval now;
	u_int16_t u16;
	MD5_CTX ctx;
	u_char *rnd = statp->_rnd == NULL ? srnd : statp->_rnd;

	gettimeofday(&now, NULL);
	u16 = (u_int16_t) (now.tv_sec ^ now.tv_usec);
	memcpy(rnd + 14, &u16, 2);
#ifndef HAVE_MD5
	MD5_Init(&ctx);
	MD5_Update(&ctx, rnd, 16);
	MD5_Final(rnd, &ctx);
#else
	MD5Init(&ctx);
	MD5Update(&ctx, rnd, 16);
	MD5Final(rnd, &ctx);
#endif
	memcpy(&u16, rnd + 14, 2);
	return ((u_int) u16);
}