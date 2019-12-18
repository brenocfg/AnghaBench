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
typedef  int /*<<< orphan*/  kadm5_ret_t ;
typedef  int /*<<< orphan*/  kadm5_principal_ent_t ;

/* Variables and functions */
 int /*<<< orphan*/  __CALL (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  modify_principal ; 

kadm5_ret_t
kadm5_modify_principal(void *server_handle,
		       kadm5_principal_ent_t princ,
		       uint32_t mask)
{
    return __CALL(modify_principal, (server_handle, princ, mask));
}