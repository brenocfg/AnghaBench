#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_4__ {TYPE_2__* fsap_data; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ svn_fs_history_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/ * fs; int /*<<< orphan*/ * current_id; void* next_copy; void* rev_hint; int /*<<< orphan*/ * path_hint; int /*<<< orphan*/  is_interesting; void* revision; int /*<<< orphan*/ * path; } ;
typedef  TYPE_2__ fs_history_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  history_vtable ; 
 int /*<<< orphan*/ * svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_fs_history_t *
assemble_history(svn_fs_t *fs,
                 const char *path,
                 svn_revnum_t revision,
                 svn_boolean_t is_interesting,
                 const char *path_hint,
                 svn_revnum_t rev_hint,
                 svn_revnum_t next_copy,
                 const svn_fs_id_t *current_id,
                 apr_pool_t *pool)
{
  svn_fs_history_t *history = apr_pcalloc(pool, sizeof(*history));
  fs_history_data_t *fhd = apr_pcalloc(pool, sizeof(*fhd));
  fhd->path = svn_fs__canonicalize_abspath(path, pool);
  fhd->revision = revision;
  fhd->is_interesting = is_interesting;
  fhd->path_hint = path_hint ? svn_fs__canonicalize_abspath(path_hint, pool)
                             : NULL;
  fhd->rev_hint = rev_hint;
  fhd->next_copy = next_copy;
  fhd->current_id = current_id ? svn_fs_fs__id_copy(current_id, pool) : NULL;
  fhd->fs = fs;

  history->vtable = &history_vtable;
  history->fsap_data = fhd;
  return history;
}