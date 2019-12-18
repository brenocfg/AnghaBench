#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_path_change_iterator_t ;
struct TYPE_9__ {char const* data; int /*<<< orphan*/  len; } ;
struct TYPE_11__ {int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_known; int /*<<< orphan*/  mergeinfo_mod; int /*<<< orphan*/  prop_mod; int /*<<< orphan*/  text_mod; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  change_kind; TYPE_1__ path; } ;
typedef  TYPE_3__ svn_fs_path_change3_t ;
struct TYPE_12__ {int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyfrom_known; int /*<<< orphan*/  mergeinfo_mod; int /*<<< orphan*/  prop_mod; int /*<<< orphan*/  text_mod; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  change_kind; } ;
typedef  TYPE_4__ svn_fs_path_change2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {scalar_t__ hi; TYPE_3__ change; } ;
typedef  TYPE_5__ fsap_iterator_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_next (scalar_t__) ; 
 char* apr_hash_this_key (scalar_t__) ; 
 int /*<<< orphan*/  apr_hash_this_key_len (scalar_t__) ; 
 TYPE_4__* apr_hash_this_val (scalar_t__) ; 

__attribute__((used)) static svn_error_t *
changes_iterator_get(svn_fs_path_change3_t **change,
                     svn_fs_path_change_iterator_t *iterator)
{
  fsap_iterator_data_t *data = iterator->fsap_data;

  if (data->hi)
    {
      const char *path = apr_hash_this_key(data->hi);
      svn_fs_path_change2_t *entry = apr_hash_this_val(data->hi);

      data->change.path.data = path;
      data->change.path.len = apr_hash_this_key_len(data->hi);
      data->change.change_kind = entry->change_kind;
      data->change.node_kind = entry->node_kind;
      data->change.text_mod = entry->text_mod;
      data->change.prop_mod = entry->prop_mod;
      data->change.mergeinfo_mod = entry->mergeinfo_mod;
      data->change.copyfrom_known = entry->copyfrom_known;
      data->change.copyfrom_rev = entry->copyfrom_rev;
      data->change.copyfrom_path = entry->copyfrom_path;

      *change = &data->change;
      data->hi = apr_hash_next(data->hi);
    }
  else
    {
      *change = NULL;
    }

  return SVN_NO_ERROR;
}