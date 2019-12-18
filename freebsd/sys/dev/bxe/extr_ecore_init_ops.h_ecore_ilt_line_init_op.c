#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ecore_ilt {int start_line; TYPE_1__* lines; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  page_mapping; } ;

/* Variables and functions */
#define  INITOP_CLEAR 130 
#define  INITOP_INIT 129 
#define  INITOP_SET 128 
 int /*<<< orphan*/  ecore_ilt_line_wr (struct bxe_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_ilt_line_init_op(struct bxe_softc *sc,
				   struct ecore_ilt *ilt, int idx, uint8_t initop)
{
	ecore_dma_addr_t	null_mapping;
	int abs_idx = ilt->start_line + idx;


	switch (initop) {
	case INITOP_INIT:
		/* set in the init-value array */
	case INITOP_SET:
		ecore_ilt_line_wr(sc, abs_idx, ilt->lines[idx].page_mapping);
		break;
	case INITOP_CLEAR:
		null_mapping = 0;
		ecore_ilt_line_wr(sc, abs_idx, null_mapping);
		break;
	}
}