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
struct bcm2835_audio_info {scalar_t__ vchi_handle; int /*<<< orphan*/  vchi_instance; } ;

/* Variables and functions */
 scalar_t__ VCHIQ_SERVICE_HANDLE_INVALID ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  vchi_disconnect (int /*<<< orphan*/ ) ; 
 int vchi_service_close (scalar_t__) ; 
 int /*<<< orphan*/  vchi_service_release (scalar_t__) ; 

__attribute__((used)) static void
bcm2835_audio_release(struct bcm2835_audio_info *sc)
{
	int success;

	if (sc->vchi_handle != VCHIQ_SERVICE_HANDLE_INVALID) {
		success = vchi_service_close(sc->vchi_handle);
		if (success != 0)
			printf("vchi_service_close failed: %d\n", success);
		vchi_service_release(sc->vchi_handle);
		sc->vchi_handle = VCHIQ_SERVICE_HANDLE_INVALID;
	}

	vchi_disconnect(sc->vchi_instance);
}