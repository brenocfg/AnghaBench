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
typedef  size_t svn_checksum_kind_t ;

/* Variables and functions */
 unsigned char const** empty_string_digests ; 

const unsigned char *
svn__empty_string_digest(svn_checksum_kind_t kind)
{
  return empty_string_digests[kind];
}