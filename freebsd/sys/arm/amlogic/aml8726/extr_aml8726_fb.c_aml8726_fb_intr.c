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
struct aml8726_fb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_FB_LOCK (struct aml8726_fb_softc*) ; 
 int /*<<< orphan*/  AML_FB_UNLOCK (struct aml8726_fb_softc*) ; 

__attribute__((used)) static void
aml8726_fb_intr(void *arg)
{
	struct aml8726_fb_softc *sc = (struct aml8726_fb_softc *)arg;

	AML_FB_LOCK(sc);

	AML_FB_UNLOCK(sc);
}