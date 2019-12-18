#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_6__* children; } ;
typedef  TYPE_7__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_20__ {void* prop_mod; void* text_mod; int /*<<< orphan*/  kind; int /*<<< orphan*/  noderev_id; int /*<<< orphan*/  path; } ;
typedef  TYPE_8__ change_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_18__ {TYPE_5__* next; } ;
struct TYPE_17__ {TYPE_4__* next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {TYPE_3__* next; scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {TYPE_2__* next; } ;
struct TYPE_14__ {TYPE_1__* next; scalar_t__ len; } ;
struct TYPE_13__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 TYPE_8__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_change_skel (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skel_err (char*) ; 
 int /*<<< orphan*/  svn_fs_base__id_parse (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__parse_change_skel(change_t **change_p,
                               svn_skel_t *skel,
                               apr_pool_t *pool)
{
  change_t *change;
  svn_fs_path_change_kind_t kind;

  /* Validate the skel. */
  if (! is_valid_change_skel(skel, &kind))
    return skel_err("change");

  /* Create the returned structure */
  change = apr_pcalloc(pool, sizeof(*change));

  /* PATH */
  change->path = apr_pstrmemdup(pool, skel->children->next->data,
                                skel->children->next->len);

  /* NODE-REV-ID */
  if (skel->children->next->next->len)
    change->noderev_id = svn_fs_base__id_parse
      (skel->children->next->next->data, skel->children->next->next->len,
       pool);

  /* KIND */
  change->kind = kind;

  /* TEXT-MOD */
  if (skel->children->next->next->next->next->len)
    change->text_mod = TRUE;

  /* PROP-MOD */
  if (skel->children->next->next->next->next->next->len)
    change->prop_mod = TRUE;

  /* Return the structure. */
  *change_p = change;
  return SVN_NO_ERROR;
}