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
struct TYPE_4__ {TYPE_2__* fsap_data; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ svn_fs_history_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_5__ {char const* path; char const* path_hint; int /*<<< orphan*/ * fs; void* rev_hint; int /*<<< orphan*/  is_interesting; void* revision; } ;
typedef  TYPE_2__ base_history_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  history_vtable ; 

__attribute__((used)) static svn_fs_history_t *
assemble_history(svn_fs_t *fs,
                 const char *path,
                 svn_revnum_t revision,
                 svn_boolean_t is_interesting,
                 const char *path_hint,
                 svn_revnum_t rev_hint,
                 apr_pool_t *pool)
{
  svn_fs_history_t *history = apr_pcalloc(pool, sizeof(*history));
  base_history_data_t *bhd = apr_pcalloc(pool, sizeof(*bhd));
  bhd->path = path;
  bhd->revision = revision;
  bhd->is_interesting = is_interesting;
  bhd->path_hint = path_hint;
  bhd->rev_hint = rev_hint;
  bhd->fs = fs;
  history->vtable = &history_vtable;
  history->fsap_data = bhd;
  return history;
}