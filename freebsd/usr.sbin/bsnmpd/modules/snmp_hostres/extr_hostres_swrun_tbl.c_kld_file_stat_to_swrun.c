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
struct swrun_entry {int perfMemory; int /*<<< orphan*/  r_tick; scalar_t__ perfCPU; void* status; void* type; int /*<<< orphan*/  index; int /*<<< orphan*/ * id; int /*<<< orphan*/ * parameters; int /*<<< orphan*/ * path; int /*<<< orphan*/ * name; } ;
struct kld_file_stat {int size; int /*<<< orphan*/  name; } ;
typedef  void* int32_t ;

/* Variables and functions */
 scalar_t__ SRS_RUNNING ; 
 scalar_t__ SRT_DEVICE_DRIVER ; 
 scalar_t__ SRT_OPERATING_SYSTEM ; 
 int /*<<< orphan*/  SWOSIndex ; 
 size_t SWR_NAME_MLEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ticks () ; 
 int /*<<< orphan*/  oid_zeroDotZero ; 
 int /*<<< orphan*/ * reallocf (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kld_file_stat_to_swrun(const struct kld_file_stat *kfs,
    struct swrun_entry *entry)
{
	size_t name_len;

	assert(kfs != NULL);
	assert(entry != NULL);

	name_len = strlen(kfs->name) + 1;
	if (name_len > SWR_NAME_MLEN)
		name_len = SWR_NAME_MLEN;

	entry->name = reallocf(entry->name, name_len);
	if (entry->name != NULL)
		strlcpy((char *)entry->name, kfs->name, name_len);

	/* FIXME: can we find the location where the module was loaded from? */
	entry->path = NULL;

	/* no parameters for kernel files (.ko) of for the kernel */
	entry->parameters = NULL;

	entry->id = &oid_zeroDotZero; /* unknown id - FIXME */

	if (strcmp(kfs->name, "kernel") == 0) {
		entry->type = (int32_t)SRT_OPERATING_SYSTEM;
		SWOSIndex = entry->index;
	} else {
		entry->type = (int32_t)SRT_DEVICE_DRIVER; /* well, not really */
	}
	entry->status = (int32_t)SRS_RUNNING;
	entry->perfCPU = 0;			/* Info not available */
	entry->perfMemory = kfs->size / 1024;	/* in kilo-bytes */
	entry->r_tick = get_ticks();
}