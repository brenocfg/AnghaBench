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
struct opalflash_softc {int /*<<< orphan*/  sc_opal_id; TYPE_1__* sc_disk; } ;
struct opal_msg {int* params; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int d_stripesize; } ;

/* Variables and functions */
 int EIO ; 
 int OPAL_ASYNC_COMPLETION ; 
 int /*<<< orphan*/  OPAL_FLASH_ERASE ; 
 int OPAL_SUCCESS ; 
 int opal_alloc_async_token () ; 
 int opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  opal_free_async_token (int) ; 
 int opal_wait_completion (struct opal_msg*,int,int) ; 

__attribute__((used)) static int
opalflash_erase(struct opalflash_softc *sc, off_t off, off_t count)
{
	struct opal_msg msg;
	int rv, token;

	/* Ensure we write aligned to a full block size. */
	if (off % sc->sc_disk->d_stripesize != 0 ||
	    count % sc->sc_disk->d_stripesize != 0)
		return (EIO);

	token = opal_alloc_async_token();

	rv = opal_call(OPAL_FLASH_ERASE, sc->sc_opal_id, off, count, token);
	if (rv == OPAL_ASYNC_COMPLETION) {
		rv = opal_wait_completion(&msg, sizeof(msg), token);
		if (rv == OPAL_SUCCESS)
			rv = msg.params[1];
	}
	opal_free_async_token(token);

	if (rv == OPAL_SUCCESS)
		rv = 0;
	else
		rv = EIO;

	return (rv);
}