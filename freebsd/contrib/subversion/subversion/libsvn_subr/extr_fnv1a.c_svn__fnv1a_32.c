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
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  FNV1_BASE_32 ; 
 int /*<<< orphan*/  fnv1a_32 (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

apr_uint32_t
svn__fnv1a_32(const void *input, apr_size_t len)
{
  return fnv1a_32(FNV1_BASE_32, input, len);
}