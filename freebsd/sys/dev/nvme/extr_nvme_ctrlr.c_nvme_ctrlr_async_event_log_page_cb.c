#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nvme_sanitize_status_page {int dummy; } ;
struct nvme_res_notification_page {int dummy; } ;
struct nvme_ns_list {scalar_t__* ns; } ;
struct nvme_health_information_page {int /*<<< orphan*/  critical_warning; } ;
struct nvme_firmware_page {int dummy; } ;
struct nvme_error_information_entry {int dummy; } ;
struct nvme_completion {int dummy; } ;
struct nvme_command_effects_page {int dummy; } ;
struct nvme_async_event_request {int log_page_id; TYPE_2__* ctrlr; int /*<<< orphan*/  log_page_size; int /*<<< orphan*/ * log_page_buffer; int /*<<< orphan*/  cpl; } ;
struct intel_log_temp_stats {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  elpe; } ;
struct TYPE_8__ {int /*<<< orphan*/  async_event_config; TYPE_1__ cdata; } ;

/* Variables and functions */
#define  INTEL_LOG_TEMP_STATS 135 
#define  NVME_LOG_CHANGED_NAMESPACE 134 
#define  NVME_LOG_COMMAND_EFFECT 133 
#define  NVME_LOG_ERROR 132 
#define  NVME_LOG_FIRMWARE_SLOT 131 
#define  NVME_LOG_HEALTH_INFORMATION 130 
#define  NVME_LOG_RES_NOTIFICATION 129 
#define  NVME_LOG_SANITIZE_STATUS 128 
 scalar_t__ NVME_MAX_NAMESPACES ; 
 int /*<<< orphan*/  intel_log_temp_stats_swapbytes (struct intel_log_temp_stats*) ; 
 int nitems (scalar_t__*) ; 
 int /*<<< orphan*/  nvme_command_effects_page_swapbytes (struct nvme_command_effects_page*) ; 
 scalar_t__ nvme_completion_is_error (struct nvme_completion const*) ; 
 int /*<<< orphan*/  nvme_ctrlr_cmd_set_async_event_config (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_ctrlr_construct_and_submit_aer (TYPE_2__*,struct nvme_async_event_request*) ; 
 int /*<<< orphan*/  nvme_ctrlr_log_critical_warnings (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_error_information_entry_swapbytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_firmware_page_swapbytes (struct nvme_firmware_page*) ; 
 int /*<<< orphan*/  nvme_health_information_page_swapbytes (struct nvme_health_information_page*) ; 
 int /*<<< orphan*/  nvme_notify_async_consumers (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_notify_ns (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  nvme_ns_list_swapbytes (struct nvme_ns_list*) ; 
 int /*<<< orphan*/  nvme_res_notification_page_swapbytes (struct nvme_res_notification_page*) ; 
 int /*<<< orphan*/  nvme_sanitize_status_page_swapbytes (struct nvme_sanitize_status_page*) ; 
 int /*<<< orphan*/  nvme_use_nvd ; 

__attribute__((used)) static void
nvme_ctrlr_async_event_log_page_cb(void *arg, const struct nvme_completion *cpl)
{
	struct nvme_async_event_request		*aer = arg;
	struct nvme_health_information_page	*health_info;
	struct nvme_ns_list			*nsl;
	struct nvme_error_information_entry	*err;
	int i;

	/*
	 * If the log page fetch for some reason completed with an error,
	 *  don't pass log page data to the consumers.  In practice, this case
	 *  should never happen.
	 */
	if (nvme_completion_is_error(cpl))
		nvme_notify_async_consumers(aer->ctrlr, &aer->cpl,
		    aer->log_page_id, NULL, 0);
	else {
		/* Convert data to host endian */
		switch (aer->log_page_id) {
		case NVME_LOG_ERROR:
			err = (struct nvme_error_information_entry *)aer->log_page_buffer;
			for (i = 0; i < (aer->ctrlr->cdata.elpe + 1); i++)
				nvme_error_information_entry_swapbytes(err++);
			break;
		case NVME_LOG_HEALTH_INFORMATION:
			nvme_health_information_page_swapbytes(
			    (struct nvme_health_information_page *)aer->log_page_buffer);
			break;
		case NVME_LOG_FIRMWARE_SLOT:
			nvme_firmware_page_swapbytes(
			    (struct nvme_firmware_page *)aer->log_page_buffer);
			break;
		case NVME_LOG_CHANGED_NAMESPACE:
			nvme_ns_list_swapbytes(
			    (struct nvme_ns_list *)aer->log_page_buffer);
			break;
		case NVME_LOG_COMMAND_EFFECT:
			nvme_command_effects_page_swapbytes(
			    (struct nvme_command_effects_page *)aer->log_page_buffer);
			break;
		case NVME_LOG_RES_NOTIFICATION:
			nvme_res_notification_page_swapbytes(
			    (struct nvme_res_notification_page *)aer->log_page_buffer);
			break;
		case NVME_LOG_SANITIZE_STATUS:
			nvme_sanitize_status_page_swapbytes(
			    (struct nvme_sanitize_status_page *)aer->log_page_buffer);
			break;
		case INTEL_LOG_TEMP_STATS:
			intel_log_temp_stats_swapbytes(
			    (struct intel_log_temp_stats *)aer->log_page_buffer);
			break;
		default:
			break;
		}

		if (aer->log_page_id == NVME_LOG_HEALTH_INFORMATION) {
			health_info = (struct nvme_health_information_page *)
			    aer->log_page_buffer;
			nvme_ctrlr_log_critical_warnings(aer->ctrlr,
			    health_info->critical_warning);
			/*
			 * Critical warnings reported through the
			 *  SMART/health log page are persistent, so
			 *  clear the associated bits in the async event
			 *  config so that we do not receive repeated
			 *  notifications for the same event.
			 */
			aer->ctrlr->async_event_config &=
			    ~health_info->critical_warning;
			nvme_ctrlr_cmd_set_async_event_config(aer->ctrlr,
			    aer->ctrlr->async_event_config, NULL, NULL);
		} else if (aer->log_page_id == NVME_LOG_CHANGED_NAMESPACE &&
		    !nvme_use_nvd) {
			nsl = (struct nvme_ns_list *)aer->log_page_buffer;
			for (i = 0; i < nitems(nsl->ns) && nsl->ns[i] != 0; i++) {
				if (nsl->ns[i] > NVME_MAX_NAMESPACES)
					break;
				nvme_notify_ns(aer->ctrlr, nsl->ns[i]);
			}
		}


		/*
		 * Pass the cpl data from the original async event completion,
		 *  not the log page fetch.
		 */
		nvme_notify_async_consumers(aer->ctrlr, &aer->cpl,
		    aer->log_page_id, aer->log_page_buffer, aer->log_page_size);
	}

	/*
	 * Repost another asynchronous event request to replace the one
	 *  that just completed.
	 */
	nvme_ctrlr_construct_and_submit_aer(aer->ctrlr, aer);
}