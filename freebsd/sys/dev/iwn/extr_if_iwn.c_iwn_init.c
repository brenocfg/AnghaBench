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
struct iwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWN_LOCK (struct iwn_softc*) ; 
 int /*<<< orphan*/  IWN_UNLOCK (struct iwn_softc*) ; 
 int iwn_init_locked (struct iwn_softc*) ; 

__attribute__((used)) static int
iwn_init(struct iwn_softc *sc)
{
	int error;

	IWN_LOCK(sc);
	error = iwn_init_locked(sc);
	IWN_UNLOCK(sc);

	return (error);
}