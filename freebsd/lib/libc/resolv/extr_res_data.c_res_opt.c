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
 int /*<<< orphan*/  _res ; 
 int res_nopt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 

int
res_opt(int n0, u_char *buf, int buflen, int anslen)
{
	return (res_nopt(&_res, n0, buf, buflen, anslen));
}