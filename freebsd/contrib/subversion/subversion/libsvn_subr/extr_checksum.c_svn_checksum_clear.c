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
struct TYPE_3__ {int /*<<< orphan*/  kind; scalar_t__ digest; } ;
typedef  TYPE_1__ svn_checksum_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIGESTSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_kind (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_checksum_clear(svn_checksum_t *checksum)
{
  SVN_ERR(validate_kind(checksum->kind));

  memset((unsigned char *) checksum->digest, 0, DIGESTSIZE(checksum->kind));
  return SVN_NO_ERROR;
}