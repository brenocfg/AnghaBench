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

/* Variables and functions */
#define  LOOP_FSCAN_DONE 138 
#define  LOOP_HAVE_ADDR 137 
#define  LOOP_HAVE_LINK 136 
#define  LOOP_LSCAN_DONE 135 
#define  LOOP_LTEST_DONE 134 
#define  LOOP_NIL 133 
#define  LOOP_READY 132 
#define  LOOP_SCANNING_FABRIC 131 
#define  LOOP_SCANNING_LOOP 130 
#define  LOOP_SYNCING_PDB 129 
#define  LOOP_TESTING_LINK 128 

const char *
isp_fc_loop_statename(int state)
{
	switch (state) {
	case LOOP_NIL:                  return "NIL";
	case LOOP_HAVE_LINK:            return "Have Link";
	case LOOP_HAVE_ADDR:            return "Have Address";
	case LOOP_TESTING_LINK:         return "Testing Link";
	case LOOP_LTEST_DONE:           return "Link Test Done";
	case LOOP_SCANNING_LOOP:        return "Scanning Loop";
	case LOOP_LSCAN_DONE:           return "Loop Scan Done";
	case LOOP_SCANNING_FABRIC:      return "Scanning Fabric";
	case LOOP_FSCAN_DONE:           return "Fabric Scan Done";
	case LOOP_SYNCING_PDB:          return "Syncing PDB";
	case LOOP_READY:                return "Ready"; 
	default:                        return "?????";
	}
}