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
struct TYPE_2__ {int /*<<< orphan*/  permanent; int /*<<< orphan*/  temp; } ;

/* Variables and functions */
 TYPE_1__* hunk_temp ; 
 int /*<<< orphan*/ * s_hunkData ; 

void Hunk_ClearTempMemory( void ) {
	if ( s_hunkData != NULL ) {
		hunk_temp->temp = hunk_temp->permanent;
	}
}