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
struct svm_softc {int /*<<< orphan*/  msr_bitmap; int /*<<< orphan*/  iopm_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SVM ; 
 int /*<<< orphan*/  SVM_IO_BITMAP_SIZE ; 
 int /*<<< orphan*/  SVM_MSR_BITMAP_SIZE ; 
 int /*<<< orphan*/  contigfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct svm_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svm_vmcleanup(void *arg)
{
	struct svm_softc *sc = arg;

	contigfree(sc->iopm_bitmap, SVM_IO_BITMAP_SIZE, M_SVM);
	contigfree(sc->msr_bitmap, SVM_MSR_BITMAP_SIZE, M_SVM);
	free(sc, M_SVM);
}