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
struct rt2560_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (struct rt2560_softc*,int,char*,char*) ; 

__attribute__((used)) static void
rt2560_wakeup_expire(struct rt2560_softc *sc)
{
	DPRINTFN(sc, 2, "%s", "wakeup expired\n");
}