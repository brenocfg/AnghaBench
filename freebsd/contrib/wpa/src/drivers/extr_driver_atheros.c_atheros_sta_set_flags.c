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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 unsigned int WPA_STA_AUTHORIZED ; 
 int atheros_set_sta_authorized (void*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
atheros_sta_set_flags(void *priv, const u8 *addr,
		      unsigned int total_flags, unsigned int flags_or,
		      unsigned int flags_and)
{
	/* For now, only support setting Authorized flag */
	if (flags_or & WPA_STA_AUTHORIZED)
		return atheros_set_sta_authorized(priv, addr, 1);
	if (!(flags_and & WPA_STA_AUTHORIZED))
		return atheros_set_sta_authorized(priv, addr, 0);
	return 0;
}