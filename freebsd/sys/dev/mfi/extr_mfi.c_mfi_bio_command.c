#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mfi_softc {TYPE_1__* mfi_qstat; } ;
struct mfi_command {int dummy; } ;
struct bio {scalar_t__ bio_driver2; } ;
struct TYPE_2__ {int q_length; } ;

/* Variables and functions */
 size_t MFIQ_FREE ; 
 uintptr_t MFI_LD_IO ; 
 uintptr_t MFI_SYS_PD_IO ; 
 struct mfi_command* mfi_build_ldio (struct mfi_softc*,struct bio*) ; 
 struct mfi_command* mfi_build_syspdio (struct mfi_softc*,struct bio*) ; 
 struct bio* mfi_dequeue_bio (struct mfi_softc*) ; 
 int /*<<< orphan*/  mfi_enqueue_bio (struct mfi_softc*,struct bio*) ; 

__attribute__((used)) static struct mfi_command *
mfi_bio_command(struct mfi_softc *sc)
{
	struct bio *bio;
	struct mfi_command *cm = NULL;

	/*reserving two commands to avoid starvation for IOCTL*/
	if (sc->mfi_qstat[MFIQ_FREE].q_length < 2) {
		return (NULL);
	}
	if ((bio = mfi_dequeue_bio(sc)) == NULL) {
		return (NULL);
	}
	if ((uintptr_t)bio->bio_driver2 == MFI_LD_IO) {
		cm = mfi_build_ldio(sc, bio);
	} else if ((uintptr_t) bio->bio_driver2 == MFI_SYS_PD_IO) {
		cm = mfi_build_syspdio(sc, bio);
	}
	if (!cm)
	    mfi_enqueue_bio(sc, bio);
	return cm;
}