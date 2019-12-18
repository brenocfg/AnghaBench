#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int addr; int back; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_buf_ptr_t ;

/* Variables and functions */
 char* cvmx_phys_to_ptr (int) ; 

__attribute__((used)) static inline char *cvm_oct_get_buffer_ptr(cvmx_buf_ptr_t packet_ptr)
{
	return cvmx_phys_to_ptr(((packet_ptr.s.addr >> 7) - packet_ptr.s.back) << 7);
}