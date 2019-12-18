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
typedef  scalar_t__ u32 ;
struct tpm_bios_log {void* bios_event_log_end; void* bios_event_log; } ;
struct tpm_chip {struct tpm_bios_log log; } ;
struct tcpa_event {int /*<<< orphan*/  event_type; int /*<<< orphan*/  event_size; } ;
struct seq_file {struct tpm_chip* private; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ do_endian_conversion (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *tpm1_bios_measurements_start(struct seq_file *m, loff_t *pos)
{
	loff_t i = 0;
	struct tpm_chip *chip = m->private;
	struct tpm_bios_log *log = &chip->log;
	void *addr = log->bios_event_log;
	void *limit = log->bios_event_log_end;
	struct tcpa_event *event;
	u32 converted_event_size;
	u32 converted_event_type;

	/* read over *pos measurements */
	do {
		event = addr;

		/* check if current entry is valid */
		if (addr + sizeof(struct tcpa_event) > limit)
			return NULL;

		converted_event_size =
		    do_endian_conversion(event->event_size);
		converted_event_type =
		    do_endian_conversion(event->event_type);

		if (((converted_event_type == 0) && (converted_event_size == 0))
		    || ((addr + sizeof(struct tcpa_event) + converted_event_size)
			> limit))
			return NULL;

		if (i++ == *pos)
			break;

		addr += (sizeof(struct tcpa_event) + converted_event_size);
	} while (1);

	return addr;
}