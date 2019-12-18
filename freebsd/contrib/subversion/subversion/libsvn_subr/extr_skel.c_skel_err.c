#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_MALFORMED_SKEL ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char const*) ; 

__attribute__((used)) static svn_error_t *
skel_err(const char *skel_type)
{
  return svn_error_createf(SVN_ERR_FS_MALFORMED_SKEL, NULL,
                           "Malformed%s%s skeleton",
                           skel_type ? " " : "",
                           skel_type ? skel_type : "");
}