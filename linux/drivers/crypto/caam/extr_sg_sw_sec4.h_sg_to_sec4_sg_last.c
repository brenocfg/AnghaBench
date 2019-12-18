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
typedef  int /*<<< orphan*/  u16 ;
struct sec4_sg_entry {int dummy; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_to_sec4_set_last (struct sec4_sg_entry*) ; 
 struct sec4_sg_entry* sg_to_sec4_sg (struct scatterlist*,int,struct sec4_sg_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sg_to_sec4_sg_last(struct scatterlist *sg, int len,
				      struct sec4_sg_entry *sec4_sg_ptr,
				      u16 offset)
{
	sec4_sg_ptr = sg_to_sec4_sg(sg, len, sec4_sg_ptr, offset);
	sg_to_sec4_set_last(sec4_sg_ptr);
}