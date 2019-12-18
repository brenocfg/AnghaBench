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
 int /*<<< orphan*/  UFM_CMD2 ; 
 scalar_t__ ufm_do_req (struct ufm_softc*,int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static int
ufm_start(struct ufm_softc *sc, void *addr)
{
	uint8_t ret;

	if (ufm_do_req(sc, UFM_CMD0,
	    0x00, 0xc7, &ret)) {
		return (EIO);
	}
	if (ufm_do_req(sc, UFM_CMD2,
	    0x01, 0x00, &ret)) {
		return (EIO);
	}
	if (ret & 0x1) {
		return (EIO);
	}
	return (0);
}