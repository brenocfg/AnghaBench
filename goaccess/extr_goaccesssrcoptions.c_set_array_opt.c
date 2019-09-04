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
 scalar_t__ str_inarray (char const*,char const**,int) ; 

__attribute__((used)) static void
set_array_opt (const char *oarg, const char *arr[], int *size, int max)
{
  if (str_inarray (oarg, arr, *size) < 0 && *size < max)
    arr[(*size)++] = oarg;
}