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
struct fw_unit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_modalias_ids (struct fw_unit*,int*) ; 
 int snprintf (char*,size_t,char*,int,int,int,int) ; 

__attribute__((used)) static int get_modalias(struct fw_unit *unit, char *buffer, size_t buffer_size)
{
	int id[] = {0, 0, 0, 0};

	get_modalias_ids(unit, id);

	return snprintf(buffer, buffer_size,
			"ieee1394:ven%08Xmo%08Xsp%08Xver%08X",
			id[0], id[1], id[2], id[3]);
}