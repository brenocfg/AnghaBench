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
typedef  int /*<<< orphan*/  svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  expanded_size; } ;
typedef  TYPE_1__ representation_t ;
struct TYPE_5__ {TYPE_1__* data_rep; } ;
typedef  TYPE_2__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

svn_error_t *
svn_fs_fs__file_length(svn_filesize_t *length,
                       node_revision_t *noderev,
                       apr_pool_t *pool)
{
  representation_t *data_rep = noderev->data_rep;
  if (!data_rep)
    {
      /* Treat "no representation" as "empty file". */
      *length = 0;
    }
  else
    {
      *length = data_rep->expanded_size;
    }

  return SVN_NO_ERROR;
}