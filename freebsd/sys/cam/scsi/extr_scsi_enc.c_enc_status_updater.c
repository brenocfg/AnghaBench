#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* poll_status ) (TYPE_2__*) ;} ;
struct TYPE_5__ {TYPE_1__ enc_vec; } ;
typedef  TYPE_2__ enc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
enc_status_updater(void *arg)
{
	enc_softc_t *enc;

	enc = arg;
	if (enc->enc_vec.poll_status != NULL)
		enc->enc_vec.poll_status(enc);
}