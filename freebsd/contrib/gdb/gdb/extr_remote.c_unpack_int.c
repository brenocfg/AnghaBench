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
 int stub_unpack_int (char*,int) ; 

__attribute__((used)) static char *
unpack_int (char *buf, int *value)
{
  *value = stub_unpack_int (buf, 8);
  return buf + 8;
}