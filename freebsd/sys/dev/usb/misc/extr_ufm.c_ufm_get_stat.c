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
typedef  int uint8_t ;
struct ufm_softc {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  UFM_CMD0 ; 
 int hz ; 
 scalar_t__ ufm_do_req (struct ufm_softc*,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ufm_get_stat(struct ufm_softc *sc, void *addr)
{
	uint8_t ret;

	/*
	 * Note, there's a 240ms settle time before the status
	 * will be valid, so sleep that amount.
	 */
	usb_pause_mtx(NULL, hz / 4);

	if (ufm_do_req(sc, UFM_CMD0,
	    0x00, 0x24, &ret)) {
		return (EIO);
	}
	*(int *)addr = ret;

	return (0);
}