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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
struct virtio_used {int dummy; } ;
struct virtio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VRING_ALIGN ; 
 size_t roundup2 (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t
vring_size(u_int qsz)
{
	size_t size;

	/* constant 3 below = va_flags, va_idx, va_used_event */
	size = sizeof(struct virtio_desc) * qsz + sizeof(uint16_t) * (3 + qsz);
	size = roundup2(size, VRING_ALIGN);

	/* constant 3 below = vu_flags, vu_idx, vu_avail_event */
	size += sizeof(uint16_t) * 3 + sizeof(struct virtio_used) * qsz;
	size = roundup2(size, VRING_ALIGN);

	return (size);
}