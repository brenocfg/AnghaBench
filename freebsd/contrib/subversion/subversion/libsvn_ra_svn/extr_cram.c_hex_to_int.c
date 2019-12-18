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

__attribute__((used)) static int hex_to_int(char c)
{
  return (c >= '0' && c <= '9') ? c - '0'
    : (c >= 'a' && c <= 'f') ? c - 'a' + 10
    : -1;
}