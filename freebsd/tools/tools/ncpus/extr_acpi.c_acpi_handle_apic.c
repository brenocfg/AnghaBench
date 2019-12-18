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
struct MADTbody {scalar_t__ body; } ;
struct MADT_local_sapic {int flags; int /*<<< orphan*/  cpu_id; } ;
struct MADT_local_apic {int flags; int /*<<< orphan*/  cpu_id; } ;
struct TYPE_2__ {struct MADT_local_sapic local_sapic; struct MADT_local_apic local_apic; } ;
struct MADT_APIC {int type; int len; TYPE_1__ body; } ;
struct ACPIsdt {uintptr_t len; scalar_t__ body; } ;

/* Variables and functions */
 int ACPI_MADT_APIC_LOCAL_FLAG_ENABLED ; 
#define  ACPI_MADT_APIC_TYPE_LOCAL_APIC 129 
#define  ACPI_MADT_APIC_TYPE_LOCAL_SAPIC 128 
 int /*<<< orphan*/  ncpu ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
acpi_handle_apic(struct ACPIsdt *sdp)
{
	struct MADTbody *madtp;
	struct MADT_APIC *mp;
	struct MADT_local_apic *apic;
	struct MADT_local_sapic *sapic;

	madtp = (struct MADTbody *) sdp->body;
	mp = (struct MADT_APIC *)madtp->body;
	while (((uintptr_t)mp) - ((uintptr_t)sdp) < sdp->len) {
		switch (mp->type) {
		case ACPI_MADT_APIC_TYPE_LOCAL_APIC:
			apic = &mp->body.local_apic;
			warnx("MADT: Found CPU APIC ID %d %s",
			    apic->cpu_id,
			    apic->flags & ACPI_MADT_APIC_LOCAL_FLAG_ENABLED ?
				"enabled" : "disabled");
			if (apic->flags & ACPI_MADT_APIC_LOCAL_FLAG_ENABLED)
				ncpu++;
			break;
		case ACPI_MADT_APIC_TYPE_LOCAL_SAPIC:
			sapic = &mp->body.local_sapic;
			warnx("MADT: Found CPU SAPIC ID %d %s",
			    sapic->cpu_id,
			    sapic->flags & ACPI_MADT_APIC_LOCAL_FLAG_ENABLED ?
				"enabled" : "disabled");
			/* XXX is enable flag the same? */
			if (sapic->flags & ACPI_MADT_APIC_LOCAL_FLAG_ENABLED)
				ncpu++;
			break;
		default:
			break;
		}
		mp = (struct MADT_APIC *) ((char *)mp + mp->len);
	}
}