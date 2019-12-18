#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {scalar_t__ revision; int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_2__ representation_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * svn_error_quick_wrap (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_txn_id (int /*<<< orphan*/  const*) ; 
 TYPE_1__* svn_fs_fs__id_unparse (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__parse_representation (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_create_wrap (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_rep_offsets(representation_t **rep_p,
                 char *string,
                 const svn_fs_id_t *noderev_id,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  svn_error_t *err
    = svn_fs_fs__parse_representation(rep_p,
                                      svn_stringbuf_create_wrap(string,
                                                                scratch_pool),
                                      result_pool,
                                      scratch_pool);
  if (err)
    {
      const svn_string_t *id_unparsed;
      const char *where;

      id_unparsed = svn_fs_fs__id_unparse(noderev_id, scratch_pool);
      where = apr_psprintf(scratch_pool,
                           _("While reading representation offsets "
                             "for node-revision '%s':"),
                           noderev_id ? id_unparsed->data : "(null)");

      return svn_error_quick_wrap(err, where);
    }

  if ((*rep_p)->revision == SVN_INVALID_REVNUM)
    if (noderev_id)
      (*rep_p)->txn_id = *svn_fs_fs__id_txn_id(noderev_id);

  return SVN_NO_ERROR;
}