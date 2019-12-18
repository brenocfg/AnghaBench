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
struct tcp_request_sock {int dummy; } ;
struct request_sock_ops {int family; int obj_size; int /*<<< orphan*/  slab; int /*<<< orphan*/  destructor; } ;
struct proto {struct request_sock_ops* rsk_prot; } ;

/* Variables and functions */
 int /*<<< orphan*/  chtls_rsk_destructor ; 
 int /*<<< orphan*/  memset (struct request_sock_ops*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void chtls_init_rsk_ops(struct proto *chtls_tcp_prot,
				      struct request_sock_ops *chtls_tcp_ops,
				      struct proto *tcp_prot, int family)
{
	memset(chtls_tcp_ops, 0, sizeof(*chtls_tcp_ops));
	chtls_tcp_ops->family = family;
	chtls_tcp_ops->obj_size = sizeof(struct tcp_request_sock);
	chtls_tcp_ops->destructor = chtls_rsk_destructor;
	chtls_tcp_ops->slab = tcp_prot->rsk_prot->slab;
	chtls_tcp_prot->rsk_prot = chtls_tcp_ops;
}