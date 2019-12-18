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
typedef  int /*<<< orphan*/  uint64_t ;
struct sec_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_EUASR ; 
 int SEC_EUASR_AESU (int /*<<< orphan*/ ) ; 
 int SEC_EUASR_AFEU (int /*<<< orphan*/ ) ; 
 int SEC_EUASR_CRCU (int /*<<< orphan*/ ) ; 
 int SEC_EUASR_DEU (int /*<<< orphan*/ ) ; 
 int SEC_EUASR_KEU (int /*<<< orphan*/ ) ; 
 int SEC_EUASR_MDEU (int /*<<< orphan*/ ) ; 
 int SEC_EUASR_PKEU (int /*<<< orphan*/ ) ; 
 int SEC_EUASR_RNGU (int /*<<< orphan*/ ) ; 
#define  SEC_EU_AESU 136 
#define  SEC_EU_AFEU 135 
#define  SEC_EU_CRCU 134 
#define  SEC_EU_DEU 133 
#define  SEC_EU_KEU 132 
#define  SEC_EU_MDEU_A 131 
#define  SEC_EU_MDEU_B 130 
#define  SEC_EU_PKEU 129 
#define  SEC_EU_RNGU 128 
 int /*<<< orphan*/  SEC_LOCK_ASSERT (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_READ (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  controller ; 

__attribute__((used)) static int
sec_eu_channel(struct sec_softc *sc, int eu)
{
	uint64_t reg;
	int channel = 0;

	SEC_LOCK_ASSERT(sc, controller);

	reg = SEC_READ(sc, SEC_EUASR);

	switch (eu) {
	case SEC_EU_AFEU:
		channel = SEC_EUASR_AFEU(reg);
		break;
	case SEC_EU_DEU:
		channel = SEC_EUASR_DEU(reg);
		break;
	case SEC_EU_MDEU_A:
	case SEC_EU_MDEU_B:
		channel = SEC_EUASR_MDEU(reg);
		break;
	case SEC_EU_RNGU:
		channel = SEC_EUASR_RNGU(reg);
		break;
	case SEC_EU_PKEU:
		channel = SEC_EUASR_PKEU(reg);
		break;
	case SEC_EU_AESU:
		channel = SEC_EUASR_AESU(reg);
		break;
	case SEC_EU_KEU:
		channel = SEC_EUASR_KEU(reg);
		break;
	case SEC_EU_CRCU:
		channel = SEC_EUASR_CRCU(reg);
		break;
	}

	return (channel - 1);
}