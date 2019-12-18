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
typedef  int /*<<< orphan*/  enc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  SES_PUBLISH_PHYSPATHS ; 
 int /*<<< orphan*/  enc_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ses_poll_status (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ses_device_found(enc_softc_t *enc)
{
	ses_poll_status(enc);
	enc_update_request(enc, SES_PUBLISH_PHYSPATHS);
}