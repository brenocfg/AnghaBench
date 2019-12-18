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
struct ifnet {struct hme_softc* if_softc; } ;
struct hme_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HME_LOCK (struct hme_softc*) ; 
 int /*<<< orphan*/  HME_UNLOCK (struct hme_softc*) ; 
 int hme_mediachange_locked (struct hme_softc*) ; 

__attribute__((used)) static int
hme_mediachange(struct ifnet *ifp)
{
	struct hme_softc *sc = ifp->if_softc;
	int error;

	HME_LOCK(sc);
	error = hme_mediachange_locked(sc);
	HME_UNLOCK(sc);
	return (error);
}