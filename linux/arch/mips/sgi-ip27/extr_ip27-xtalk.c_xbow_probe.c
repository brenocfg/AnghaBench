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
typedef  scalar_t__ nasid_t ;
typedef  int /*<<< orphan*/  lboard_t ;
typedef  int /*<<< orphan*/  klxbow_t ;

/* Variables and functions */
 int ENODEV ; 
 int HUB_WIDGET_ID_MAX ; 
 int HUB_WIDGET_ID_MIN ; 
 int /*<<< orphan*/  KLSTRUCT_XBOW ; 
 int /*<<< orphan*/  KLTYPE_MIDPLANE8 ; 
 scalar_t__ KL_CONFIG_INFO (scalar_t__) ; 
 scalar_t__ XBOW_PORT_IS_ENABLED (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ XBOW_PORT_NASID (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  XBOW_PORT_TYPE_HUB (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ XBOW_PORT_TYPE_IO (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ find_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_lboard (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_one_port (scalar_t__,unsigned int,unsigned int) ; 

__attribute__((used)) static int xbow_probe(nasid_t nasid)
{
	lboard_t *brd;
	klxbow_t *xbow_p;
	unsigned masterwid, i;

	/*
	 * found xbow, so may have multiple bridges
	 * need to probe xbow
	 */
	brd = find_lboard((lboard_t *)KL_CONFIG_INFO(nasid), KLTYPE_MIDPLANE8);
	if (!brd)
		return -ENODEV;

	xbow_p = (klxbow_t *)find_component(brd, NULL, KLSTRUCT_XBOW);
	if (!xbow_p)
		return -ENODEV;

	/*
	 * Okay, here's a xbow. Let's arbitrate and find
	 * out if we should initialize it. Set enabled
	 * hub connected at highest or lowest widget as
	 * master.
	 */
#ifdef WIDGET_A
	i = HUB_WIDGET_ID_MAX + 1;
	do {
		i--;
	} while ((!XBOW_PORT_TYPE_HUB(xbow_p, i)) ||
		 (!XBOW_PORT_IS_ENABLED(xbow_p, i)));
#else
	i = HUB_WIDGET_ID_MIN - 1;
	do {
		i++;
	} while ((!XBOW_PORT_TYPE_HUB(xbow_p, i)) ||
		 (!XBOW_PORT_IS_ENABLED(xbow_p, i)));
#endif

	masterwid = i;
	if (nasid != XBOW_PORT_NASID(xbow_p, i))
		return 1;

	for (i = HUB_WIDGET_ID_MIN; i <= HUB_WIDGET_ID_MAX; i++) {
		if (XBOW_PORT_IS_ENABLED(xbow_p, i) &&
		    XBOW_PORT_TYPE_IO(xbow_p, i))
			probe_one_port(nasid, i, masterwid);
	}

	return 0;
}