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
#define  CISS_CMD_STATUS_ABORTED 140 
#define  CISS_CMD_STATUS_ABORT_FAILED 139 
#define  CISS_CMD_STATUS_CONNECTION_LOST 138 
#define  CISS_CMD_STATUS_DATA_OVERRUN 137 
#define  CISS_CMD_STATUS_DATA_UNDERRUN 136 
#define  CISS_CMD_STATUS_HARDWARE_ERROR 135 
#define  CISS_CMD_STATUS_INVALID_COMMAND 134 
#define  CISS_CMD_STATUS_PROTOCOL_ERROR 133 
#define  CISS_CMD_STATUS_SUCCESS 132 
#define  CISS_CMD_STATUS_TARGET_STATUS 131 
#define  CISS_CMD_STATUS_TIMEOUT 130 
#define  CISS_CMD_STATUS_UNABORTABLE 129 
#define  CISS_CMD_STATUS_UNSOLICITED_ABORT 128 

__attribute__((used)) static const char *
ciss_name_command_status(int status)
{
    switch(status) {
    case CISS_CMD_STATUS_SUCCESS:
	return("success");
    case CISS_CMD_STATUS_TARGET_STATUS:
	return("target status");
    case CISS_CMD_STATUS_DATA_UNDERRUN:
	return("data underrun");
    case CISS_CMD_STATUS_DATA_OVERRUN:
	return("data overrun");
    case CISS_CMD_STATUS_INVALID_COMMAND:
	return("invalid command");
    case CISS_CMD_STATUS_PROTOCOL_ERROR:
	return("protocol error");
    case CISS_CMD_STATUS_HARDWARE_ERROR:
	return("hardware error");
    case CISS_CMD_STATUS_CONNECTION_LOST:
	return("connection lost");
    case CISS_CMD_STATUS_ABORTED:
	return("aborted");
    case CISS_CMD_STATUS_ABORT_FAILED:
	return("abort failed");
    case CISS_CMD_STATUS_UNSOLICITED_ABORT:
	return("unsolicited abort");
    case CISS_CMD_STATUS_TIMEOUT:
	return("timeout");
    case CISS_CMD_STATUS_UNABORTABLE:
	return("unabortable");
    }
    return("unknown status");
}