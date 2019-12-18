#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {void* a; void* b; } ;
typedef  TYPE_1__ be128 ;

/* Variables and functions */
 int be64_to_cpu (void*) ; 
 void* cpu_to_be64 (int) ; 
 int* gf128mul_table_le ; 

__attribute__((used)) static void gf128mul_x8_lle(be128 *x)
{
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);
	u64 _tt = gf128mul_table_le[b & 0xff];

	x->b = cpu_to_be64((b >> 8) | (a << 56));
	x->a = cpu_to_be64((a >> 8) ^ (_tt << 48));
}