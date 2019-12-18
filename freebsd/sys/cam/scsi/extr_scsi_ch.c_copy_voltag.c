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
struct volume_tag {char* vif; int /*<<< orphan*/  vsn; } ;
struct changer_voltag {char* cv_volid; int /*<<< orphan*/  cv_serial; } ;

/* Variables and functions */
 int CH_VOLTAG_MAXLEN ; 
 int /*<<< orphan*/  scsi_2btoul (int /*<<< orphan*/ ) ; 

__attribute__((used)) static	void
copy_voltag(struct changer_voltag *uvoltag, struct volume_tag *voltag)
{
	int i;
	for (i=0; i<CH_VOLTAG_MAXLEN; i++) {
		char c = voltag->vif[i];
		if (c && c != ' ')
			uvoltag->cv_volid[i] = c;
	        else
			break;
	}
	uvoltag->cv_serial = scsi_2btoul(voltag->vsn);
}