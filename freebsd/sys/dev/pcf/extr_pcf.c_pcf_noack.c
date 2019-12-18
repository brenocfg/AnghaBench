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
struct pcf_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int LRB ; 
 int /*<<< orphan*/  PCF_ASSERT_LOCKED (struct pcf_softc*) ; 
 int pcf_get_S1 (struct pcf_softc*) ; 

__attribute__((used)) static int
pcf_noack(struct pcf_softc *sc, int timeout)
{
	int noack;
	int k = timeout/10;

	PCF_ASSERT_LOCKED(sc);
	do {
		noack = pcf_get_S1(sc) & LRB;
		if (!noack)
			break;
		DELAY(10);				/* XXX wait 10 us */
	} while (k--);

	return (noack);
}