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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  type ;
struct s390_load_data {int dummy; } ;
struct kimage {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  entry ;
typedef  int /*<<< orphan*/  crash_size ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ KEXEC_TYPE_CRASH ; 
 scalar_t__ KEXEC_TYPE_DEFAULT ; 
 scalar_t__ STARTUP_KDUMP_OFFSET ; 
 scalar_t__ STARTUP_NORMAL_OFFSET ; 
 TYPE_1__ crashk_res ; 
 int kexec_purgatory_get_set_symbol (struct kimage*,char*,scalar_t__*,int,int) ; 

__attribute__((used)) static int kexec_file_update_purgatory(struct kimage *image,
				       struct s390_load_data *data)
{
	u64 entry, type;
	int ret;

	if (image->type == KEXEC_TYPE_CRASH) {
		entry = STARTUP_KDUMP_OFFSET;
		type = KEXEC_TYPE_CRASH;
	} else {
		entry = STARTUP_NORMAL_OFFSET;
		type = KEXEC_TYPE_DEFAULT;
	}

	ret = kexec_purgatory_get_set_symbol(image, "kernel_entry", &entry,
					     sizeof(entry), false);
	if (ret)
		return ret;

	ret = kexec_purgatory_get_set_symbol(image, "kernel_type", &type,
					     sizeof(type), false);
	if (ret)
		return ret;

	if (image->type == KEXEC_TYPE_CRASH) {
		u64 crash_size;

		ret = kexec_purgatory_get_set_symbol(image, "crash_start",
						     &crashk_res.start,
						     sizeof(crashk_res.start),
						     false);
		if (ret)
			return ret;

		crash_size = crashk_res.end - crashk_res.start + 1;
		ret = kexec_purgatory_get_set_symbol(image, "crash_size",
						     &crash_size,
						     sizeof(crash_size),
						     false);
	}
	return ret;
}