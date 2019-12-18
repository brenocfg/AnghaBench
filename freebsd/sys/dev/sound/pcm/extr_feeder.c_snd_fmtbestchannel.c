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
typedef  int /*<<< orphan*/  u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  snd_fmtbestfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

u_int32_t
snd_fmtbestchannel(u_int32_t fmt, u_int32_t *fmts)
{
	return snd_fmtbestfunc(fmt, fmts, 1);
}