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
typedef  scalar_t__ u_int ;
struct sockaddr_dl {int dummy; } ;
struct kue_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  KUE_MCFILT (struct kue_softc*,scalar_t__) ; 
 scalar_t__ KUE_MCFILTCNT (struct kue_softc*) ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
kue_copy_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct kue_softc *sc = arg;

	if (cnt >= KUE_MCFILTCNT(sc))
		return (1);

	memcpy(KUE_MCFILT(sc, cnt), LLADDR(sdl), ETHER_ADDR_LEN);

	return (1);
}