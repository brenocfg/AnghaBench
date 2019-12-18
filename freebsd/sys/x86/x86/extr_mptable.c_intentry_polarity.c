#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* int_entry_ptr ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
struct TYPE_3__ {int int_flags; int /*<<< orphan*/  src_bus_irq; int /*<<< orphan*/  src_bus_id; } ;

/* Variables and functions */
 int INTENTRY_FLAGS_POLARITY ; 
#define  INTENTRY_FLAGS_POLARITY_ACTIVEHI 130 
#define  INTENTRY_FLAGS_POLARITY_ACTIVELO 129 
#define  INTENTRY_FLAGS_POLARITY_CONFORM 128 
 int INTR_POLARITY_HIGH ; 
 int INTR_POLARITY_LOW ; 
 int conforming_polarity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static enum intr_polarity
intentry_polarity(int_entry_ptr intr)
{

	switch (intr->int_flags & INTENTRY_FLAGS_POLARITY) {
	case INTENTRY_FLAGS_POLARITY_CONFORM:
		return (conforming_polarity(intr->src_bus_id,
			    intr->src_bus_irq));
	case INTENTRY_FLAGS_POLARITY_ACTIVEHI:
		return (INTR_POLARITY_HIGH);
	case INTENTRY_FLAGS_POLARITY_ACTIVELO:
		return (INTR_POLARITY_LOW);
	default:
		panic("Bogus interrupt flags");
	}
}