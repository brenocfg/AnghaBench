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
struct bsm_socket_type {int /*<<< orphan*/  bst_bsm_socket_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSM_SOCK_UNKNOWN ; 
 struct bsm_socket_type* bsm_lookup_local_socket_type (int) ; 

u_short
au_socket_type_to_bsm(int local_socket_type)
{
	const struct bsm_socket_type *bstp;

	bstp = bsm_lookup_local_socket_type(local_socket_type);
	if (bstp == NULL)
		return (BSM_SOCK_UNKNOWN);
	return (bstp->bst_bsm_socket_type);
}