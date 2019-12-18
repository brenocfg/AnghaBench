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
typedef  int /*<<< orphan*/  uint16_t ;
struct bwn_mac {int dummy; } ;
struct b2055_inittab_entry {int flags; int /*<<< orphan*/  ghz2; int /*<<< orphan*/  ghz5; } ;

/* Variables and functions */
 int B2055_INITTAB_ENTRY_OK ; 
 int B2055_INITTAB_UPLOAD ; 
 int /*<<< orphan*/  BWN_MACCTL ; 
 int /*<<< orphan*/  BWN_READ_4 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,unsigned int,int /*<<< orphan*/ ) ; 
 struct b2055_inittab_entry* b2055_inittab ; 
 unsigned int nitems (struct b2055_inittab_entry*) ; 

void b2055_upload_inittab(struct bwn_mac *mac,
			  bool ghz5, bool ignore_uploadflag)
{
	const struct b2055_inittab_entry *e;
	unsigned int i, writes = 0;
	uint16_t value;

	for (i = 0; i < nitems(b2055_inittab); i++) {
		e = &(b2055_inittab[i]);
		if (!(e->flags & B2055_INITTAB_ENTRY_OK))
			continue;
		if ((e->flags & B2055_INITTAB_UPLOAD) || ignore_uploadflag) {
			if (ghz5)
				value = e->ghz5;
			else
				value = e->ghz2;
			BWN_RF_WRITE(mac, i, value);
			if (++writes % 4 == 0)
				BWN_READ_4(mac, BWN_MACCTL); /* flush */
		}
	}
	/* One final flush */
	BWN_READ_4(mac, BWN_MACCTL);
}