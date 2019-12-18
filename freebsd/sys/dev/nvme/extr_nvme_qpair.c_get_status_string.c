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
typedef  int uint16_t ;
struct nvme_status_string {int sc; char const* str; } ;

/* Variables and functions */
#define  NVME_SCT_COMMAND_SPECIFIC 132 
#define  NVME_SCT_GENERIC 131 
#define  NVME_SCT_MEDIA_ERROR 130 
#define  NVME_SCT_PATH_RELATED 129 
#define  NVME_SCT_VENDOR_SPECIFIC 128 
 struct nvme_status_string* command_specific_status ; 
 struct nvme_status_string* generic_status ; 
 struct nvme_status_string* media_error_status ; 
 struct nvme_status_string* path_related_status ; 

__attribute__((used)) static const char *
get_status_string(uint16_t sct, uint16_t sc)
{
	struct nvme_status_string *entry;

	switch (sct) {
	case NVME_SCT_GENERIC:
		entry = generic_status;
		break;
	case NVME_SCT_COMMAND_SPECIFIC:
		entry = command_specific_status;
		break;
	case NVME_SCT_MEDIA_ERROR:
		entry = media_error_status;
		break;
	case NVME_SCT_PATH_RELATED:
		entry = path_related_status;
		break;
	case NVME_SCT_VENDOR_SPECIFIC:
		return ("VENDOR SPECIFIC");
	default:
		return ("RESERVED");
	}

	while (entry->sc != 0xFFFF) {
		if (entry->sc == sc)
			return (entry->str);
		entry++;
	}
	return (entry->str);
}