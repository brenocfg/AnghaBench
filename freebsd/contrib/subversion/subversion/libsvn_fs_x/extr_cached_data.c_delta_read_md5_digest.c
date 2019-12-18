#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char const* md5_digest; } ;
typedef  TYPE_1__ delta_read_baton_t ;

/* Variables and functions */

__attribute__((used)) static const unsigned char *
delta_read_md5_digest(void *baton)
{
  delta_read_baton_t *drb = baton;
  return drb->md5_digest;
}