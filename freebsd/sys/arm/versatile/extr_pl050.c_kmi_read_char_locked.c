#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct kmi_softc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kb_count; struct kmi_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBD_IS_ACTIVE (TYPE_1__*) ; 
 int /*<<< orphan*/  KMIDATA ; 
 int /*<<< orphan*/  KMIIR ; 
 int KMIIR_RXINTR ; 
 int /*<<< orphan*/  KMI_CTX_LOCK_ASSERT () ; 
 int NOKEY ; 
 int pl050_kmi_read_4 (struct kmi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
kmi_read_char_locked(keyboard_t *kbd, int wait)
{
	struct kmi_softc *sc = kbd->kb_data;
	uint32_t reg, data;

	KMI_CTX_LOCK_ASSERT();

	if (!KBD_IS_ACTIVE(kbd))
		return (NOKEY);

	reg = pl050_kmi_read_4(sc, KMIIR);
	if (reg & KMIIR_RXINTR) {
		data = pl050_kmi_read_4(sc, KMIDATA);
		return (data);
	}

	++kbd->kb_count;
	return (NOKEY);
}