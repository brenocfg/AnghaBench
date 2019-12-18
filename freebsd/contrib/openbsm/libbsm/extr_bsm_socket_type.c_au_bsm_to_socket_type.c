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
typedef  int /*<<< orphan*/  u_short ;
struct bsm_socket_type {int bst_local_socket_type; } ;

/* Variables and functions */
 struct bsm_socket_type* bsm_lookup_bsm_socket_type (int /*<<< orphan*/ ) ; 

int
au_bsm_to_socket_type(u_short bsm_socket_type, int *local_socket_typep)
{
	const struct bsm_socket_type *bstp;

	bstp = bsm_lookup_bsm_socket_type(bsm_socket_type);
	if (bstp == NULL || bstp->bst_local_socket_type)
		return (-1);
	*local_socket_typep = bstp->bst_local_socket_type;
	return (0);
}