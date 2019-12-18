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
 int KADM5_AUX_ATTRIBUTES ; 
 int KADM5_LAST_FAILED ; 
 int KADM5_LAST_PWD_CHANGE ; 
 int KADM5_LAST_SUCCESS ; 
 int KADM5_MKVNO ; 
 int KADM5_MOD_NAME ; 
 int KADM5_MOD_TIME ; 
 int /*<<< orphan*/  modify_principal (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

kadm5_ret_t
kadm5_s_modify_principal(void *server_handle,
			 kadm5_principal_ent_t princ,
			 uint32_t mask)
{
    return modify_principal(server_handle, princ, mask,
			    KADM5_LAST_PWD_CHANGE | KADM5_MOD_TIME
			    | KADM5_MOD_NAME | KADM5_MKVNO
			    | KADM5_AUX_ATTRIBUTES | KADM5_LAST_SUCCESS
			    | KADM5_LAST_FAILED);
}