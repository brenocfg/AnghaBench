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
typedef  scalar_t__ uint8_t ;
struct saf1761_otg_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAF1761_WRITE_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SOTG_CTRL_FUNC ; 
 scalar_t__ SOTG_CTRL_FUNC_CLBUF ; 
 int /*<<< orphan*/  SOTG_EP_INDEX ; 
 scalar_t__ SOTG_EP_INDEX_DIR_IN ; 
 scalar_t__ SOTG_EP_INDEX_DIR_OUT ; 
 scalar_t__ SOTG_EP_INDEX_ENDP_INDEX_SHIFT ; 
 int /*<<< orphan*/  SOTG_EP_TYPE ; 
 scalar_t__ SOTG_EP_TYPE_ENABLE ; 
 scalar_t__ UE_CONTROL ; 
 scalar_t__ UE_DIR_IN ; 

__attribute__((used)) static void
saf1761_otg_clear_stall_sub_locked(struct saf1761_otg_softc *sc,
    uint8_t ep_no, uint8_t ep_type, uint8_t ep_dir)
{
	if (ep_type == UE_CONTROL) {
		/* clearing stall is not needed */
		return;
	}
	/* select the correct endpoint */
	SAF1761_WRITE_LE_4(sc, SOTG_EP_INDEX,
	    (ep_no << SOTG_EP_INDEX_ENDP_INDEX_SHIFT) |
	    ((ep_dir == UE_DIR_IN) ? SOTG_EP_INDEX_DIR_IN :
	    SOTG_EP_INDEX_DIR_OUT));

	/* disable endpoint */
	SAF1761_WRITE_LE_4(sc, SOTG_EP_TYPE, 0);
	/* enable endpoint again - will clear data toggle */
	SAF1761_WRITE_LE_4(sc, SOTG_EP_TYPE, ep_type | SOTG_EP_TYPE_ENABLE);

	/* clear buffer */
	SAF1761_WRITE_LE_4(sc, SOTG_CTRL_FUNC, SOTG_CTRL_FUNC_CLBUF);
	/* clear stall */
	SAF1761_WRITE_LE_4(sc, SOTG_CTRL_FUNC, 0);
}