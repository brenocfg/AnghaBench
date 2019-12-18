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
struct exfat_vbr {int /*<<< orphan*/  ev_fsname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct exfat_vbr*) ; 
 scalar_t__ read_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int
fstyp_exfat(FILE *fp, char *label, size_t size)
{
	struct exfat_vbr *ev;

	ev = (struct exfat_vbr *)read_buf(fp, 0, 512);
	if (ev == NULL || strncmp(ev->ev_fsname, "EXFAT   ", 8) != 0)
		goto fail;

	/*
	 * Reading the volume label requires walking the root directory to look
	 * for a special label file.  Left as an exercise for the reader.
	 */
	free(ev);
	return (0);

fail:
	free(ev);
	return (1);
}