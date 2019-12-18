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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  mkimg_uuid_t ;
typedef  int /*<<< orphan*/  gen ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  osdep_uuidgen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_testing ; 

void
mkimg_uuid(mkimg_uuid_t *uuid)
{
	static uint8_t gen[sizeof(mkimg_uuid_t)];
	u_int i;

	if (!unit_testing) {
		osdep_uuidgen(uuid);
		return;
	}

	for (i = 0; i < sizeof(gen); i++)
		gen[i]++;
	memcpy(uuid, gen, sizeof(*uuid));
}