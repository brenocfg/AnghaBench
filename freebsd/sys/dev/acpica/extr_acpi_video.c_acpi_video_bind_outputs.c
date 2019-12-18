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
struct acpi_video_softc {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_video_bind_outputs_subr ; 
 int /*<<< orphan*/  vid_enum_outputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_video_softc*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static void
acpi_video_bind_outputs(struct acpi_video_softc *sc)
{

	ACPI_SERIAL_ASSERT(video);
	vid_enum_outputs(sc->handle, acpi_video_bind_outputs_subr, sc);
}