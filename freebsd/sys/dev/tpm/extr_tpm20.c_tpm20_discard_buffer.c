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
struct tpm_sc {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  buf_cv; scalar_t__ pending_data_length; int /*<<< orphan*/  buf; int /*<<< orphan*/  discard_buffer_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_BUFSIZE ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tpm20_discard_buffer(void *arg)
{
	struct tpm_sc *sc;

	sc = (struct tpm_sc *)arg;
	if (callout_pending(&sc->discard_buffer_callout))
		return;

	sx_xlock(&sc->dev_lock);

	memset(sc->buf, 0, TPM_BUFSIZE);
	sc->pending_data_length = 0;

	cv_signal(&sc->buf_cv);
	sx_xunlock(&sc->dev_lock);

	device_printf(sc->dev,
	    "User failed to read buffer in time\n");
}