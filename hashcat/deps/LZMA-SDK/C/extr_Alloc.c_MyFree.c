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
 int /*<<< orphan*/  PRINT_FREE (char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  g_allocCount ; 

void MyFree(void *address)
{
  PRINT_FREE("Free    ", g_allocCount, address);
  
  free(address);
}