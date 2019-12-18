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
struct TYPE_3__ {int /*<<< orphan*/  manifest_start; } ;
typedef  TYPE_1__ packed_revprops_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int SVN_INT64_BUFFER_SIZE ; 
 scalar_t__ svn__i64toa (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_size_t
get_min_filename_len(packed_revprops_t *revprops)
{
  char number_buffer[SVN_INT64_BUFFER_SIZE];

  /* The revprop filenames have the format <REV>.<COUNT> - with <REV> being
   * at least the first rev in the shard and <COUNT> having at least one
   * digit.  Thus, the minimum is 2 + #decimal places in the start rev.
   */
  return svn__i64toa(number_buffer, revprops->manifest_start) + 2;
}