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
struct ac97_info {int dummy; } ;

/* Variables and functions */
 int ac97_getsubvendor (struct ac97_info*) ; 
 int ac97_rdcd (struct ac97_info*,int) ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int,int) ; 

void alc655_patch(struct ac97_info* codec)
{
	/*
	 * MSI (Micro-Star International) specific EAPD quirk.
	 */
	switch (ac97_getsubvendor(codec)) {
	case 0x00611462:	/* MSI S250 */
	case 0x01311462:	/* MSI S270 */
	case 0x01611462:	/* LG K1 Express */
	case 0x03511462:	/* MSI L725 */
		ac97_wrcd(codec, 0x7a, ac97_rdcd(codec, 0x7a) & 0xfffd);
		break;
	case 0x10ca1734:
		/*
		 * Amilo Pro V2055 with ALC655 has phone out by default
		 * disabled (surround on), leaving us only with internal
		 * speakers. This should really go to mixer. We write the
		 * Data Flow Control reg.
		 */
		ac97_wrcd(codec, 0x6a, ac97_rdcd(codec, 0x6a) | 0x0001);
		break;
	default:
		break;
	}
}