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
struct TYPE_4__ {struct kmi_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBD_IS_ACTIVE (TYPE_1__*) ; 
 int /*<<< orphan*/  KMIIR ; 
 int KMIIR_RXINTR ; 
 int /*<<< orphan*/  KMI_CTX_LOCK_ASSERT () ; 
 int pl050_kmi_read_4 (struct kmi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kmi_check(keyboard_t *kbd)
{
	struct kmi_softc *sc = kbd->kb_data;
	uint32_t reg;

	KMI_CTX_LOCK_ASSERT();

	if (!KBD_IS_ACTIVE(kbd))
		return (0);

	reg = pl050_kmi_read_4(sc, KMIIR);
	return (reg & KMIIR_RXINTR);
}