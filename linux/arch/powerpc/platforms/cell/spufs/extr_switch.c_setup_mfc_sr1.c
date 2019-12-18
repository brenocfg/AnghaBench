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
struct spu_state {int dummy; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 int MFC_STATE1_BUS_TLBIE_MASK ; 
 int MFC_STATE1_MASTER_RUN_CONTROL_MASK ; 
 int MFC_STATE1_RELOCATE_MASK ; 
 int /*<<< orphan*/  spu_mfc_sr1_set (struct spu*,int) ; 

__attribute__((used)) static inline void setup_mfc_sr1(struct spu_state *csa, struct spu *spu)
{
	/* Save, Step 30:
	 * Restore, Step 18:
	 *     Write MFC_SR1 with MFC_SR1[D=0,S=1] and
	 *     MFC_SR1[TL,R,Pr,T] set correctly for the
	 *     OS specific environment.
	 *
	 *     Implementation note: The SPU-side code
	 *     for save/restore is privileged, so the
	 *     MFC_SR1[Pr] bit is not set.
	 *
	 */
	spu_mfc_sr1_set(spu, (MFC_STATE1_MASTER_RUN_CONTROL_MASK |
			      MFC_STATE1_RELOCATE_MASK |
			      MFC_STATE1_BUS_TLBIE_MASK));
}