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
typedef  int /*<<< orphan*/  uint64_t ;
struct ps3pic_softc {int sc_ipi_virq; int /*<<< orphan*/ * sc_ipi_outlet; scalar_t__ bitmap_thread1; scalar_t__ bitmap_thread0; scalar_t__ mask_thread1; scalar_t__ mask_thread0; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  FALSE ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_PS3PIC ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ contigmalloc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ps3pic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_configure_irq_state_bitmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_connect_irq_plug_ext (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_construct_event_receive_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lv1_get_logical_ppe_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfctrl () ; 
 int /*<<< orphan*/  powerpc_register_pic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtophys (scalar_t__) ; 

__attribute__((used)) static int
ps3pic_attach(device_t dev)
{
	struct ps3pic_softc *sc;
	uint64_t ppe;
	int thread;

	sc = device_get_softc(dev);

	sc->bitmap_thread0 = contigmalloc(128 /* 512 bits * 2 */, M_PS3PIC,
	    M_NOWAIT | M_ZERO, 0, BUS_SPACE_MAXADDR, 64 /* alignment */,
	    PAGE_SIZE /* boundary */);
	sc->mask_thread0 = sc->bitmap_thread0 + 4;
	sc->bitmap_thread1 = sc->bitmap_thread0 + 8;
	sc->mask_thread1 = sc->bitmap_thread0 + 12;

	lv1_get_logical_ppe_id(&ppe);
	thread = 32 - fls(mfctrl());
	lv1_configure_irq_state_bitmap(ppe, thread,
	    vtophys(sc->bitmap_thread0));

	sc->sc_ipi_virq = 63;

#ifdef SMP
	lv1_configure_irq_state_bitmap(ppe, !thread,
	    vtophys(sc->bitmap_thread1));

	/* Map both IPIs to the same VIRQ to avoid changes in intr_machdep */
	lv1_construct_event_receive_port(&sc->sc_ipi_outlet[0]);
	lv1_connect_irq_plug_ext(ppe, thread, sc->sc_ipi_virq,
	    sc->sc_ipi_outlet[0], 0);
	lv1_construct_event_receive_port(&sc->sc_ipi_outlet[1]);
	lv1_connect_irq_plug_ext(ppe, !thread, sc->sc_ipi_virq,
	    sc->sc_ipi_outlet[1], 0);
#endif

	powerpc_register_pic(dev, 0, sc->sc_ipi_virq, 1, FALSE);
	return (0);
}