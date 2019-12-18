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
typedef  int uint16_t ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int SSD_SKS_PROGRESS_DENOM ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int,int,int) ; 

void
scsi_progress_sbuf(struct sbuf *sb, uint16_t progress)
{
	sbuf_printf(sb, "Progress: %d%% (%d/%d) complete",
		    (progress * 100) / SSD_SKS_PROGRESS_DENOM,
		    progress, SSD_SKS_PROGRESS_DENOM);
}