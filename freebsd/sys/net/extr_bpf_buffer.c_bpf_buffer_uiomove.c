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
typedef  int /*<<< orphan*/  u_int ;
struct uio {int dummy; } ;
struct bpf_d {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int uiomove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uio*) ; 

int
bpf_buffer_uiomove(struct bpf_d *d, caddr_t buf, u_int len, struct uio *uio)
{

	return (uiomove(buf, len, uio));
}