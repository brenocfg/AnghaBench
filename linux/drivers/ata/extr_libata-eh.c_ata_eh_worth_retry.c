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
struct ata_queued_cmd {int err_mask; int flags; } ;

/* Variables and functions */
 int AC_ERR_DEV ; 
 int AC_ERR_INVALID ; 
 int AC_ERR_MEDIA ; 
 int ATA_QCFLAG_IO ; 

__attribute__((used)) static inline int ata_eh_worth_retry(struct ata_queued_cmd *qc)
{
	if (qc->err_mask & AC_ERR_MEDIA)
		return 0;	/* don't retry media errors */
	if (qc->flags & ATA_QCFLAG_IO)
		return 1;	/* otherwise retry anything from fs stack */
	if (qc->err_mask & AC_ERR_INVALID)
		return 0;	/* don't retry these */
	return qc->err_mask != AC_ERR_DEV;  /* retry if not dev error */
}