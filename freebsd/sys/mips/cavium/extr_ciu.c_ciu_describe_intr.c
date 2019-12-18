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
struct resource {int dummy; } ;
struct intr_event {int /*<<< orphan*/  ie_fullname; } ;
typedef  int /*<<< orphan*/  mips_intrcnt_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CIU_IRQ_EN0_BEGIN ; 
 int CIU_IRQ_EN0_END ; 
 int CIU_IRQ_EN1_BEGIN ; 
 struct intr_event** ciu_en0_intr_events ; 
 int /*<<< orphan*/ * ciu_en0_intrcnt ; 
 struct intr_event** ciu_en1_intr_events ; 
 int /*<<< orphan*/ * ciu_en1_intrcnt ; 
 int intr_event_describe_handler (struct intr_event*,void*,char const*) ; 
 int /*<<< orphan*/  mips_intrcnt_setname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static int
ciu_describe_intr(device_t bus, device_t child, struct resource *res,
		  void *cookie, const char *descr)
{
	struct intr_event *event;
	mips_intrcnt_t intrcnt;
	int error;
	int irq;
	
	irq = rman_get_start(res);
	if (irq <= CIU_IRQ_EN0_END) {
		event = ciu_en0_intr_events[irq - CIU_IRQ_EN0_BEGIN];
		intrcnt = ciu_en0_intrcnt[irq - CIU_IRQ_EN0_BEGIN];
	} else {
		event = ciu_en1_intr_events[irq - CIU_IRQ_EN1_BEGIN];
		intrcnt = ciu_en1_intrcnt[irq - CIU_IRQ_EN1_BEGIN];
	}

	error = intr_event_describe_handler(event, cookie, descr);
	if (error != 0)
		return (error);

	mips_intrcnt_setname(intrcnt, event->ie_fullname);

	return (0);
}