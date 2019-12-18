#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct tpm_sc {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * Interrupts; } ;
struct TYPE_6__ {int /*<<< orphan*/ * Interrupts; } ;
struct TYPE_8__ {TYPE_2__ ExtendedIrq; TYPE_1__ Irq; } ;
struct TYPE_9__ {int Type; TYPE_3__ Data; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_RESOURCE ;

/* Variables and functions */
#define  ACPI_RESOURCE_TYPE_EXTENDED_IRQ 129 
#define  ACPI_RESOURCE_TYPE_IRQ 128 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  TPM_INT_VECTOR ; 
 int /*<<< orphan*/  WR1 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
tpmtis_get_SIRQ_channel(ACPI_RESOURCE *res, void *arg)
{
	struct tpm_sc *sc;
	uint8_t channel;

	sc = (struct tpm_sc *)arg;

	switch (res->Type) {
	case ACPI_RESOURCE_TYPE_IRQ:
		channel = res->Data.Irq.Interrupts[0];
		break;
	case ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		channel = res->Data.ExtendedIrq.Interrupts[0];
		break;
	default:
		return (AE_OK);
	}

	WR1(sc, TPM_INT_VECTOR, channel);
	return (AE_OK);
}