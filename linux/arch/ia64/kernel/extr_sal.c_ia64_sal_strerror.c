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

const char *
ia64_sal_strerror (long status)
{
	const char *str;
	switch (status) {
	      case 0: str = "Call completed without error"; break;
	      case 1: str = "Effect a warm boot of the system to complete "
			      "the update"; break;
	      case -1: str = "Not implemented"; break;
	      case -2: str = "Invalid argument"; break;
	      case -3: str = "Call completed with error"; break;
	      case -4: str = "Virtual address not registered"; break;
	      case -5: str = "No information available"; break;
	      case -6: str = "Insufficient space to add the entry"; break;
	      case -7: str = "Invalid entry_addr value"; break;
	      case -8: str = "Invalid interrupt vector"; break;
	      case -9: str = "Requested memory not available"; break;
	      case -10: str = "Unable to write to the NVM device"; break;
	      case -11: str = "Invalid partition type specified"; break;
	      case -12: str = "Invalid NVM_Object id specified"; break;
	      case -13: str = "NVM_Object already has the maximum number "
				"of partitions"; break;
	      case -14: str = "Insufficient space in partition for the "
				"requested write sub-function"; break;
	      case -15: str = "Insufficient data buffer space for the "
				"requested read record sub-function"; break;
	      case -16: str = "Scratch buffer required for the write/delete "
				"sub-function"; break;
	      case -17: str = "Insufficient space in the NVM_Object for the "
				"requested create sub-function"; break;
	      case -18: str = "Invalid value specified in the partition_rec "
				"argument"; break;
	      case -19: str = "Record oriented I/O not supported for this "
				"partition"; break;
	      case -20: str = "Bad format of record to be written or "
				"required keyword variable not "
				"specified"; break;
	      default: str = "Unknown SAL status code"; break;
	}
	return str;
}