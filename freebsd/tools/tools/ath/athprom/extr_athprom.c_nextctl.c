#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ee_numCtls; int* ee_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  curmode ; 
 TYPE_1__ eeprom ; 
 int /*<<< orphan*/  headerInfo11A ; 
 int /*<<< orphan*/  headerInfo11B ; 
 int /*<<< orphan*/  headerInfo11G ; 

int
nextctl(int start)
{
	int i;

	for (i = start; i < eeprom.ee_numCtls && eeprom.ee_ctl[i]; i++) {
		switch (eeprom.ee_ctl[i] & 3) {
		case 0: case 3:
			if (curmode != headerInfo11A)
				continue;
			break;
		case 1:
			if (curmode != headerInfo11B)
				continue;
			break;
		case 2:
			if (curmode != headerInfo11G)
				continue;
			break;
		}
		return i;
	}
	return -1;
}