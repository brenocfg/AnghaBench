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
struct sock {int sk_wmem_queued; } ;
struct chtls_dev {int max_host_sndbuf; } ;

/* Variables and functions */

__attribute__((used)) static int csk_mem_free(struct chtls_dev *cdev, struct sock *sk)
{
	return (cdev->max_host_sndbuf - sk->sk_wmem_queued);
}