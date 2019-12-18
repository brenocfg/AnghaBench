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
typedef  int /*<<< orphan*/  uint8_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxe_get_leader_lock_resource (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_trylock_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
bxe_trylock_leader_lock(struct bxe_softc *sc)
{
    return (bxe_trylock_hw_lock(sc, bxe_get_leader_lock_resource(sc)));
}