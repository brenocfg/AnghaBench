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
struct hd_struct {scalar_t__ start_sect; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ part_nr_sects_read (struct hd_struct*) ; 

__attribute__((used)) static inline int sector_in_part(struct hd_struct *part, sector_t sector)
{
	return part->start_sect <= sector &&
		sector < part->start_sect + part_nr_sects_read(part);
}