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

/* Variables and functions */
 unsigned char const* svn__empty_string_digest (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 

const unsigned char *
svn_md5_empty_string_digest(void)
{
  return svn__empty_string_digest(svn_checksum_md5);
}