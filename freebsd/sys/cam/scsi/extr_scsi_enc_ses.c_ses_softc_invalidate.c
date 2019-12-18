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
struct TYPE_4__ {int /*<<< orphan*/  ses_requests; } ;
typedef  TYPE_1__ ses_softc_t ;
struct TYPE_5__ {TYPE_1__* enc_private; } ;
typedef  TYPE_2__ enc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  ses_terminate_control_requests (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ses_softc_invalidate(enc_softc_t *enc)
{
	ses_softc_t *ses;

	ses = enc->enc_private;
	ses_terminate_control_requests(&ses->ses_requests, ENXIO);
}