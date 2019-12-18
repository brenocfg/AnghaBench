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
struct twe_softc {int /*<<< orphan*/  twe_ich; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twe_init (struct twe_softc*) ; 

__attribute__((used)) static void
twe_intrhook(void *arg)
{
    struct twe_softc		*sc = (struct twe_softc *)arg;

    /* pull ourselves off the intrhook chain */
    config_intrhook_disestablish(&sc->twe_ich);

    /* call core startup routine */
    twe_init(sc);
}