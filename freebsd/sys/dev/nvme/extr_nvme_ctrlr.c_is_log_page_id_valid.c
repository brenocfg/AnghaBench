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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  NVME_LOG_CHANGED_NAMESPACE 134 
#define  NVME_LOG_COMMAND_EFFECT 133 
#define  NVME_LOG_ERROR 132 
#define  NVME_LOG_FIRMWARE_SLOT 131 
#define  NVME_LOG_HEALTH_INFORMATION 130 
#define  NVME_LOG_RES_NOTIFICATION 129 
#define  NVME_LOG_SANITIZE_STATUS 128 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static boolean_t
is_log_page_id_valid(uint8_t page_id)
{

	switch (page_id) {
	case NVME_LOG_ERROR:
	case NVME_LOG_HEALTH_INFORMATION:
	case NVME_LOG_FIRMWARE_SLOT:
	case NVME_LOG_CHANGED_NAMESPACE:
	case NVME_LOG_COMMAND_EFFECT:
	case NVME_LOG_RES_NOTIFICATION:
	case NVME_LOG_SANITIZE_STATUS:
		return (TRUE);
	}

	return (FALSE);
}