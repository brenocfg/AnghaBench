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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vring_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paddr_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
_vq_record(uint32_t offs, int i, volatile struct vring_desc *vd,
	struct iovec *iov, int n_iov, uint16_t *flags) {

	if (i >= n_iov)
		return;

	iov[i].iov_base = paddr_map(offs, be64toh(vd->addr),
				be32toh(vd->len));
	iov[i].iov_len = be32toh(vd->len);
	if (flags != NULL)
		flags[i] = be16toh(vd->flags);
}