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
struct nvme_command_effects_page {void** iocs; void** acs; } ;

/* Variables and functions */
 void* le32toh (void*) ; 

__attribute__((used)) static inline
void	nvme_command_effects_page_swapbytes(struct nvme_command_effects_page *s)
{
	int i;

	for (i = 0; i < 256; i++)
		s->acs[i] = le32toh(s->acs[i]);
	for (i = 0; i < 256; i++)
		s->iocs[i] = le32toh(s->iocs[i]);
}