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
struct sbuf {int dummy; } ;
struct acpi_cpu_softc {int cpu_cx_count; TYPE_1__* cpu_cx_states; int /*<<< orphan*/  cpu_cx_supported; } ;
struct TYPE_2__ {int /*<<< orphan*/  trans_lat; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_trim (struct sbuf*) ; 

__attribute__((used)) static void
acpi_cpu_cx_list(struct acpi_cpu_softc *sc)
{
    struct sbuf sb;
    int i;

    /*
     * Set up the list of Cx states
     */
    sbuf_new(&sb, sc->cpu_cx_supported, sizeof(sc->cpu_cx_supported),
	SBUF_FIXEDLEN);
    for (i = 0; i < sc->cpu_cx_count; i++)
	sbuf_printf(&sb, "C%d/%d/%d ", i + 1, sc->cpu_cx_states[i].type,
	    sc->cpu_cx_states[i].trans_lat);
    sbuf_trim(&sb);
    sbuf_finish(&sb);
}