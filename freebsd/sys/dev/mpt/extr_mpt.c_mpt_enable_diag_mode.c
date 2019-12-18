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
struct mpt_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int MPI_DIAG_DRWE ; 
 int MPI_WRSEQ_1ST_KEY_VALUE ; 
 int MPI_WRSEQ_2ND_KEY_VALUE ; 
 int MPI_WRSEQ_3RD_KEY_VALUE ; 
 int MPI_WRSEQ_4TH_KEY_VALUE ; 
 int MPI_WRSEQ_5TH_KEY_VALUE ; 
 int /*<<< orphan*/  MPT_OFFSET_DIAGNOSTIC ; 
 int /*<<< orphan*/  MPT_OFFSET_SEQUENCE ; 
 int mpt_read (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_write (struct mpt_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mpt_enable_diag_mode(struct mpt_softc *mpt)
{
	int try;

	try = 20;
	while (--try) {

		if ((mpt_read(mpt, MPT_OFFSET_DIAGNOSTIC) & MPI_DIAG_DRWE) != 0)
			break;

		/* Enable diagnostic registers */
		mpt_write(mpt, MPT_OFFSET_SEQUENCE, 0xFF);
		mpt_write(mpt, MPT_OFFSET_SEQUENCE, MPI_WRSEQ_1ST_KEY_VALUE);
		mpt_write(mpt, MPT_OFFSET_SEQUENCE, MPI_WRSEQ_2ND_KEY_VALUE);
		mpt_write(mpt, MPT_OFFSET_SEQUENCE, MPI_WRSEQ_3RD_KEY_VALUE);
		mpt_write(mpt, MPT_OFFSET_SEQUENCE, MPI_WRSEQ_4TH_KEY_VALUE);
		mpt_write(mpt, MPT_OFFSET_SEQUENCE, MPI_WRSEQ_5TH_KEY_VALUE);

		DELAY(100000);
	}
	if (try == 0)
		return (EIO);
	return (0);
}