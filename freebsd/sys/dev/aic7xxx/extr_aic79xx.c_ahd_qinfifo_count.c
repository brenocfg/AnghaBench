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
typedef  scalar_t__ u_int ;
struct ahd_softc {scalar_t__ qinfifonext; int /*<<< orphan*/  qinfifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHD_MODE_CCHAN_MSK ; 
 scalar_t__ AHD_QIN_WRAP (scalar_t__) ; 
 scalar_t__ NUM_ELEMENTS (int /*<<< orphan*/ ) ; 
 scalar_t__ ahd_get_snscb_qoff (struct ahd_softc*) ; 

__attribute__((used)) static int
ahd_qinfifo_count(struct ahd_softc *ahd)
{
	u_int qinpos;
	u_int wrap_qinpos;
	u_int wrap_qinfifonext;

	AHD_ASSERT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	qinpos = ahd_get_snscb_qoff(ahd);
	wrap_qinpos = AHD_QIN_WRAP(qinpos);
	wrap_qinfifonext = AHD_QIN_WRAP(ahd->qinfifonext);
	if (wrap_qinfifonext >= wrap_qinpos)
		return (wrap_qinfifonext - wrap_qinpos);
	else
		return (wrap_qinfifonext
		      + NUM_ELEMENTS(ahd->qinfifo) - wrap_qinpos);
}