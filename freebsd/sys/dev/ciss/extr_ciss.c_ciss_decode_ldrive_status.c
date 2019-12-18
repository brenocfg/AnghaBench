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
 int CISS_LD_NONEXISTENT ; 
 int CISS_LD_OFFLINE ; 
 int CISS_LD_ONLINE ; 
#define  CISS_LSTATUS_BECOMING_READY 138 
#define  CISS_LSTATUS_EXPANDING 137 
#define  CISS_LSTATUS_FAILED 136 
#define  CISS_LSTATUS_INTERIM_RECOVERY 135 
#define  CISS_LSTATUS_MISSING_PDRIVE 134 
#define  CISS_LSTATUS_NOT_CONFIGURED 133 
#define  CISS_LSTATUS_OK 132 
#define  CISS_LSTATUS_QUEUED_FOR_EXPANSION 131 
#define  CISS_LSTATUS_READY_RECOVERY 130 
#define  CISS_LSTATUS_RECOVERING 129 
#define  CISS_LSTATUS_WRONG_PDRIVE 128 

__attribute__((used)) static int
ciss_decode_ldrive_status(int status)
{
    switch(status) {
    case CISS_LSTATUS_NOT_CONFIGURED:
	return(CISS_LD_NONEXISTENT);

    case CISS_LSTATUS_OK:
    case CISS_LSTATUS_INTERIM_RECOVERY:
    case CISS_LSTATUS_READY_RECOVERY:
    case CISS_LSTATUS_RECOVERING:
    case CISS_LSTATUS_EXPANDING:
    case CISS_LSTATUS_QUEUED_FOR_EXPANSION:
	return(CISS_LD_ONLINE);

    case CISS_LSTATUS_FAILED:
    case CISS_LSTATUS_WRONG_PDRIVE:
    case CISS_LSTATUS_MISSING_PDRIVE:
    case CISS_LSTATUS_BECOMING_READY:
    default:
	return(CISS_LD_OFFLINE);
    }
}