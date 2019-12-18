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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct bpf_d {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

void
bpf_buffer_append_bytes(struct bpf_d *d, caddr_t buf, u_int offset,
    void *src, u_int len)
{
	u_char *src_bytes;

	src_bytes = (u_char *)src;
	bcopy(src_bytes, buf + offset, len);
}