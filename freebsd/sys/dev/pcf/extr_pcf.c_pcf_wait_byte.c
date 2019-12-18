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
 int IIC_ETIMEOUT ; 
 int /*<<< orphan*/  PCF_ASSERT_LOCKED (struct pcf_softc*) ; 
 int PIN ; 
 int TIMEOUT ; 
 int pcf_get_S1 (struct pcf_softc*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
pcf_wait_byte(struct pcf_softc *sc)
{
	int counter = TIMEOUT;

	PCF_ASSERT_LOCKED(sc);
	while (counter--) {

		if ((pcf_get_S1(sc) & PIN) == 0)
			return (0);
	}

#ifdef PCFDEBUG
	printf("pcf: timeout!\n");
#endif

	return (IIC_ETIMEOUT);
}