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
struct archive_entry {size_t mac_metadata_size; int /*<<< orphan*/ * mac_metadata; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

void
archive_entry_copy_mac_metadata(struct archive_entry *entry,
    const void *p, size_t s)
{
  free(entry->mac_metadata);
  if (p == NULL || s == 0) {
    entry->mac_metadata = NULL;
    entry->mac_metadata_size = 0;
  } else {
    entry->mac_metadata_size = s;
    entry->mac_metadata = malloc(s);
    if (entry->mac_metadata == NULL)
      abort();
    memcpy(entry->mac_metadata, p, s);
  }
}