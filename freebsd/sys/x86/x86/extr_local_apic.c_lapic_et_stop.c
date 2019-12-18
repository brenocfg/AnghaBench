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
struct lapic {int /*<<< orphan*/  la_timer_mode; } ;
struct eventtimer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAT_MODE_UNDEF ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_id ; 
 int /*<<< orphan*/  lapic_timer_stop (struct lapic*) ; 
 struct lapic* lapics ; 

__attribute__((used)) static int
lapic_et_stop(struct eventtimer *et)
{
	struct lapic *la;

	la = &lapics[PCPU_GET(apic_id)];
	lapic_timer_stop(la);
	la->la_timer_mode = LAT_MODE_UNDEF;
	return (0);
}