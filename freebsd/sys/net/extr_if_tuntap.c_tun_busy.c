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
struct tuntap_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUN_LOCK (struct tuntap_softc*) ; 
 int /*<<< orphan*/  TUN_UNLOCK (struct tuntap_softc*) ; 
 int tun_busy_locked (struct tuntap_softc*) ; 

__attribute__((used)) static int
tun_busy(struct tuntap_softc *tp)
{
	int ret;

	TUN_LOCK(tp);
	ret = tun_busy_locked(tp);
	TUN_UNLOCK(tp);
	return (ret);
}