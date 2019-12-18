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
typedef  int u_long ;
struct opalflash_softc {int /*<<< orphan*/  sc_opal_id; scalar_t__ sc_erase; TYPE_1__* sc_disk; } ;
struct opal_msg {int* params; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int d_sectorsize; } ;

/* Variables and functions */
 int EIO ; 
 int MIN (int,scalar_t__) ; 
 int OPAL_ASYNC_COMPLETION ; 
 int /*<<< orphan*/  OPAL_FLASH_WRITE ; 
 int OPAL_SUCCESS ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int opal_alloc_async_token () ; 
 int opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  opal_free_async_token (int) ; 
 int opal_wait_completion (struct opal_msg*,int,int) ; 
 int opalflash_erase (struct opalflash_softc*,int,int) ; 
 int /*<<< orphan*/  vtophys (scalar_t__) ; 

__attribute__((used)) static int
opalflash_write(struct opalflash_softc *sc, off_t off,
    caddr_t data, off_t count)
{
	struct opal_msg msg;
	int rv, size, token;

	/* Ensure we write aligned to a full block size. */
	if (off % sc->sc_disk->d_sectorsize != 0 ||
	    count % sc->sc_disk->d_sectorsize != 0)
		return (EIO);

	if (sc->sc_erase) {
	    /* Erase the full block first, then write in page chunks. */
	    rv = opalflash_erase(sc, off, count);
	    if (rv != 0)
		    return (rv);
	}

	token = opal_alloc_async_token();

	/*
	 * Write one page at a time.  It's not guaranteed that the buffer is
	 * physically contiguous.
	 */
	while (count > 0) {
		size = MIN(count, PAGE_SIZE);
		size = MIN(size, PAGE_SIZE - ((u_long)data & PAGE_MASK));
		rv = opal_call(OPAL_FLASH_WRITE, sc->sc_opal_id, off,
		    vtophys(data), size, token);
		if (rv == OPAL_ASYNC_COMPLETION) {
			rv = opal_wait_completion(&msg, sizeof(msg), token);
			if (rv == OPAL_SUCCESS)
				rv = msg.params[1];
		}
		if (rv != OPAL_SUCCESS)
			break;
		count -= size;
		off += size;
		data += size;
	}
	opal_free_async_token(token);

	if (rv == OPAL_SUCCESS)
		rv = 0;
	else
		rv = EIO;

	return (rv);
}