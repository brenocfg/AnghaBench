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
typedef  int u_int32_t ;
struct iop_softc {TYPE_1__* reg; } ;
struct TYPE_2__ {int iqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

u_int32_t
iop_get_mfa(struct iop_softc *sc)
{
    u_int32_t mfa;
    int timeout = 10000;

    while ((mfa = sc->reg->iqueue) == 0xffffffff && timeout) {
	DELAY(1000);
	timeout--;
    }
    if (!timeout)
	printf("pstiop: no free mfa\n");
    return mfa;
}