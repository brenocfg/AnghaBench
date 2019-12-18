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
typedef  scalar_t__ svn_checksum_kind_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_BAD_CHECKSUM_KIND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_checksum_fnv1a_32x4 ; 
 scalar_t__ svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
validate_kind(svn_checksum_kind_t kind)
{
  if (kind >= svn_checksum_md5 && kind <= svn_checksum_fnv1a_32x4)
    return SVN_NO_ERROR;
  else
    return svn_error_create(SVN_ERR_BAD_CHECKSUM_KIND, NULL, NULL);
}