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
struct tuntap_softc {int /*<<< orphan*/  tun_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  tuninit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tunifinit(void *xtp)
{
	struct tuntap_softc *tp;

	tp = (struct tuntap_softc *)xtp;
	tuninit(tp->tun_ifp);
}