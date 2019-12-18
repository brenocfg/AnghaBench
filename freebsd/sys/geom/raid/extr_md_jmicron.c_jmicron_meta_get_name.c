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
struct jmicron_raid_conf {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
jmicron_meta_get_name(struct jmicron_raid_conf *meta, char *buf)
{
	int i;

	strncpy(buf, meta->name, 16);
	buf[16] = 0;
	for (i = 15; i >= 0; i--) {
		if (buf[i] > 0x20)
			break;
		buf[i] = 0;
	}
}