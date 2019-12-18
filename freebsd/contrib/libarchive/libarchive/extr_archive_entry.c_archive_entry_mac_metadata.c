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
struct archive_entry {size_t mac_metadata_size; void const* mac_metadata; } ;

/* Variables and functions */

const void *
archive_entry_mac_metadata(struct archive_entry *entry, size_t *s)
{
  *s = entry->mac_metadata_size;
  return entry->mac_metadata;
}