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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  revision; int /*<<< orphan*/  fs; int /*<<< orphan*/ * rfile; } ;
typedef  TYPE_1__ shared_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t*
auto_open_shared_file(shared_file_t *file)
{
  if (file->rfile == NULL)
    SVN_ERR(svn_fs_x__rev_file_init(&file->rfile, file->fs,
                                    file->revision, file->pool));

  return SVN_NO_ERROR;
}