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
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

u_int
dmar_nd2mask(u_int nd)
{
	static const u_int masks[] = {
		0x000f,	/* nd == 0 */
		0x002f,	/* nd == 1 */
		0x00ff,	/* nd == 2 */
		0x02ff,	/* nd == 3 */
		0x0fff,	/* nd == 4 */
		0x2fff,	/* nd == 5 */
		0xffff,	/* nd == 6 */
		0x0000,	/* nd == 7 reserved */
	};

	KASSERT(nd <= 6, ("number of domains %d", nd));
	return (masks[nd]);
}