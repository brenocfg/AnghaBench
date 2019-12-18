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
struct TYPE_5__ {TYPE_1__* data_rep; } ;
typedef  TYPE_2__ svn_fs_x__noderev_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {scalar_t__ expanded_size; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

svn_error_t *
svn_fs_x__file_length(svn_filesize_t *length,
                      svn_fs_x__noderev_t *noderev)
{
  if (noderev->data_rep)
    *length = noderev->data_rep->expanded_size;
  else
    *length = 0;

  return SVN_NO_ERROR;
}