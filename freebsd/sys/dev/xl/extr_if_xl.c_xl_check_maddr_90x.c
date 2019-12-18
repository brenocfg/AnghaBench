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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XL_RXFILTER_ALLMULTI ; 

__attribute__((used)) static u_int
xl_check_maddr_90x(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	uint8_t *rxfilt = arg;

	*rxfilt |= XL_RXFILTER_ALLMULTI;

	return (1);
}