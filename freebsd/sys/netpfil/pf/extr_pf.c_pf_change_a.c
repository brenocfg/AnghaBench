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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  ao ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 int /*<<< orphan*/  pf_cksum_fixup (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void
pf_change_a(void *a, u_int16_t *c, u_int32_t an, u_int8_t u)
{
	u_int32_t	ao;

	memcpy(&ao, a, sizeof(ao));
	memcpy(a, &an, sizeof(u_int32_t));
	*c = pf_cksum_fixup(pf_cksum_fixup(*c, ao / 65536, an / 65536, u),
	    ao % 65536, an % 65536, u);
}