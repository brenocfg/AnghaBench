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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_attrib_table_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 struct scsi_attrib_table_entry* scsi_find_attrib_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_mam_attr_table ; 

struct scsi_attrib_table_entry *
scsi_get_attrib_entry(uint32_t id)
{
	return (scsi_find_attrib_entry(scsi_mam_attr_table,
	    nitems(scsi_mam_attr_table), id));
}