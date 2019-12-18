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
struct nvme_health_information_page {void* ttftmt2; void* ttftmt1; void* tmt2tc; void* tmt1tc; void** temp_sensor; void* error_temp_time; void* warning_temp_time; scalar_t__ num_error_info_log_entries; scalar_t__ media_errors; scalar_t__ unsafe_shutdowns; scalar_t__ power_on_hours; scalar_t__ power_cycles; scalar_t__ controller_busy_time; scalar_t__ host_write_commands; scalar_t__ host_read_commands; scalar_t__ data_units_written; scalar_t__ data_units_read; void* temperature; } ;

/* Variables and functions */
 void* le16toh (void*) ; 
 void* le32toh (void*) ; 
 int /*<<< orphan*/  nvme_le128toh (void*) ; 

__attribute__((used)) static inline
void	nvme_health_information_page_swapbytes(struct nvme_health_information_page *s)
{
	int i;

	s->temperature = le16toh(s->temperature);
	nvme_le128toh((void *)s->data_units_read);
	nvme_le128toh((void *)s->data_units_written);
	nvme_le128toh((void *)s->host_read_commands);
	nvme_le128toh((void *)s->host_write_commands);
	nvme_le128toh((void *)s->controller_busy_time);
	nvme_le128toh((void *)s->power_cycles);
	nvme_le128toh((void *)s->power_on_hours);
	nvme_le128toh((void *)s->unsafe_shutdowns);
	nvme_le128toh((void *)s->media_errors);
	nvme_le128toh((void *)s->num_error_info_log_entries);
	s->warning_temp_time = le32toh(s->warning_temp_time);
	s->error_temp_time = le32toh(s->error_temp_time);
	for (i = 0; i < 8; i++)
		s->temp_sensor[i] = le16toh(s->temp_sensor[i]);
	s->tmt1tc = le32toh(s->tmt1tc);
	s->tmt2tc = le32toh(s->tmt2tc);
	s->ttftmt1 = le32toh(s->ttftmt1);
	s->ttftmt2 = le32toh(s->ttftmt2);
}