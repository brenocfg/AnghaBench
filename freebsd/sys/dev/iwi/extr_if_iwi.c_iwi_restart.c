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
struct iwi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwi_init (struct iwi_softc*) ; 

__attribute__((used)) static void
iwi_restart(void *arg, int npending)
{
	struct iwi_softc *sc = arg;

	iwi_init(sc);
}