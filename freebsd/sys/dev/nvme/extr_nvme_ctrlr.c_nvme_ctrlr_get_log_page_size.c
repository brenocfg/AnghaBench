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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct nvme_sanitize_status_page {int dummy; } ;
struct nvme_res_notification_page {int dummy; } ;
struct nvme_ns_list {int dummy; } ;
struct nvme_health_information_page {int dummy; } ;
struct nvme_firmware_page {int dummy; } ;
struct nvme_error_information_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  elpe; } ;
struct nvme_controller {TYPE_1__ cdata; } ;
struct nvme_command_effects_page {int dummy; } ;

/* Variables and functions */
#define  NVME_LOG_CHANGED_NAMESPACE 134 
#define  NVME_LOG_COMMAND_EFFECT 133 
#define  NVME_LOG_ERROR 132 
#define  NVME_LOG_FIRMWARE_SLOT 131 
#define  NVME_LOG_HEALTH_INFORMATION 130 
#define  NVME_LOG_RES_NOTIFICATION 129 
#define  NVME_LOG_SANITIZE_STATUS 128 
 int /*<<< orphan*/  NVME_MAX_AER_LOG_SIZE ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
nvme_ctrlr_get_log_page_size(struct nvme_controller *ctrlr, uint8_t page_id)
{
	uint32_t	log_page_size;

	switch (page_id) {
	case NVME_LOG_ERROR:
		log_page_size = min(
		    sizeof(struct nvme_error_information_entry) *
		    (ctrlr->cdata.elpe + 1), NVME_MAX_AER_LOG_SIZE);
		break;
	case NVME_LOG_HEALTH_INFORMATION:
		log_page_size = sizeof(struct nvme_health_information_page);
		break;
	case NVME_LOG_FIRMWARE_SLOT:
		log_page_size = sizeof(struct nvme_firmware_page);
		break;
	case NVME_LOG_CHANGED_NAMESPACE:
		log_page_size = sizeof(struct nvme_ns_list);
		break;
	case NVME_LOG_COMMAND_EFFECT:
		log_page_size = sizeof(struct nvme_command_effects_page);
		break;
	case NVME_LOG_RES_NOTIFICATION:
		log_page_size = sizeof(struct nvme_res_notification_page);
		break;
	case NVME_LOG_SANITIZE_STATUS:
		log_page_size = sizeof(struct nvme_sanitize_status_page);
		break;
	default:
		log_page_size = 0;
		break;
	}

	return (log_page_size);
}