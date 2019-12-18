#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int spa_import_flags; scalar_t__ spa_mode; } ;
typedef  TYPE_1__ spa_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ FREAD ; 
 int ZFS_IMPORT_CHECKPOINT ; 

boolean_t
spa_importing_readonly_checkpoint(spa_t *spa)
{
	return ((spa->spa_import_flags & ZFS_IMPORT_CHECKPOINT) &&
	    spa->spa_mode == FREAD);
}