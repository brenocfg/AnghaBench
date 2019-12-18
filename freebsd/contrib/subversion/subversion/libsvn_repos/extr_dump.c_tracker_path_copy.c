#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  path_tracker_t ;
struct TYPE_3__ {int /*<<< orphan*/  exists; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_path; } ;
typedef  TYPE_1__ path_tracker_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_stringbuf_set (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* tracker_add_entry (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
tracker_path_copy(path_tracker_t *tracker,
                  const char *path,
                  const char *copyfrom_path,
                  svn_revnum_t copyfrom_rev)
{
  path_tracker_entry_t *entry = tracker_add_entry(tracker, path);

  svn_stringbuf_set(entry->copyfrom_path, copyfrom_path);
  entry->copyfrom_rev = copyfrom_rev;
  entry->exists = TRUE;
}