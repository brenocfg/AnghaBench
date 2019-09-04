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
struct TYPE_3__ {int /*<<< orphan*/  filelen; scalar_t__ fileofs; } ;
typedef  TYPE_1__ lump_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_BlockChecksum (scalar_t__,int /*<<< orphan*/ ) ; 
 int LittleLong (int /*<<< orphan*/ ) ; 
 scalar_t__ cmod_base ; 

unsigned CM_LumpChecksum(lump_t *lump) {
	return LittleLong (Com_BlockChecksum (cmod_base + lump->fileofs, lump->filelen));
}