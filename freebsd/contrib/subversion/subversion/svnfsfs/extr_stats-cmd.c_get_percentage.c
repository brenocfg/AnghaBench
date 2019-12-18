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
typedef  double apr_uint64_t ;

/* Variables and functions */

__attribute__((used)) static int
get_percentage(apr_uint64_t part,
               apr_uint64_t total)
{
  /* This include total == 0. */
  if (part >= total)
    return 100;

  /* Standard case. */
  return (int)(part * 100.0 / total);
}