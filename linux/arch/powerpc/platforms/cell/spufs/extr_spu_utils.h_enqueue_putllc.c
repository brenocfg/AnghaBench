#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* ui; } ;
typedef  TYPE_1__ addr64 ;

/* Variables and functions */
 int /*<<< orphan*/  MFC_Cmd ; 
 int /*<<< orphan*/  MFC_EAH ; 
 int /*<<< orphan*/  MFC_EAL ; 
 int /*<<< orphan*/  MFC_LSA ; 
 int /*<<< orphan*/  MFC_Size ; 
 int /*<<< orphan*/  MFC_TagID ; 
 int /*<<< orphan*/  spu_writech (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void enqueue_putllc(addr64 lscsa_ea)
{
	unsigned int ls = 0;
	unsigned int size = 128;
	unsigned int tag_id = 0;
	unsigned int cmd = 0xB4;	/* PUTLLC */

	/* Save, Step 12:
	 * Restore, Step 7:
	 *    Send a PUTLLC (tag 0) command to the MFC using
	 *    an effective address in the CSA in order to
	 *    remove any possible lock-line reservation.
	 */
	spu_writech(MFC_LSA, ls);
	spu_writech(MFC_EAH, lscsa_ea.ui[0]);
	spu_writech(MFC_EAL, lscsa_ea.ui[1]);
	spu_writech(MFC_Size, size);
	spu_writech(MFC_TagID, tag_id);
	spu_writech(MFC_Cmd, cmd);
}