#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ich_func; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* softc_cleanup ) (struct enc_softc*) ;} ;
struct enc_softc {TYPE_2__ enc_boot_hold_ch; TYPE_1__ enc_vec; } ;
struct cam_periph {struct enc_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_FREE (struct enc_softc*) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct enc_softc*) ; 

__attribute__((used)) static void
enc_dtor(struct cam_periph *periph)
{
	struct enc_softc *enc;

	enc = periph->softc;

	/* If the sub-driver has a cleanup routine, call it */
	if (enc->enc_vec.softc_cleanup != NULL)
		enc->enc_vec.softc_cleanup(enc);

	if (enc->enc_boot_hold_ch.ich_func != NULL) {
		config_intrhook_disestablish(&enc->enc_boot_hold_ch);
		enc->enc_boot_hold_ch.ich_func = NULL;
	}

	ENC_FREE(enc);
}