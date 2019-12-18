#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* data; size_t len; } ;
struct TYPE_7__ {int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_known; int /*<<< orphan*/  mergeinfo_mod; int /*<<< orphan*/  prop_mod; int /*<<< orphan*/  text_mod; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  change_kind; TYPE_1__ path; } ;
typedef  TYPE_2__ svn_fs_path_change3_t ;
struct TYPE_8__ {int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_known; int /*<<< orphan*/  mergeinfo_mod; int /*<<< orphan*/  prop_mod; int /*<<< orphan*/  text_mod; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  change_kind; } ;
typedef  TYPE_3__ svn_fs_path_change2_t ;

/* Variables and functions */

__attribute__((used)) static void
convert_path_change(svn_fs_path_change3_t *output,
                    const char *path,
                    size_t path_len,
                    svn_fs_path_change2_t *entry)
{
  output->path.data = path;
  output->path.len = path_len;
  output->change_kind = entry->change_kind;
  output->node_kind = entry->node_kind;
  output->text_mod = entry->text_mod;
  output->prop_mod = entry->prop_mod;
  output->mergeinfo_mod = entry->mergeinfo_mod;
  output->copyfrom_known = entry->copyfrom_known;
  output->copyfrom_rev = entry->copyfrom_rev;
  output->copyfrom_path = entry->copyfrom_path;
}