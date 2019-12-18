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
struct cvmx_bootmem_desc {int dummy; } ;

/* Variables and functions */
 struct cvmx_bootmem_desc* cvmx_bootmem_desc ; 

struct cvmx_bootmem_desc *cvmx_bootmem_get_desc(void)
{
	return cvmx_bootmem_desc;
}