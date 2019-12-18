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
typedef  int /*<<< orphan*/  kadm5_server_context ;
typedef  scalar_t__ kadm5_ret_t ;

/* Variables and functions */
 scalar_t__ kadm5_log_end (int /*<<< orphan*/ *) ; 
 scalar_t__ kadm5_log_get_version (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kadm5_log_init (int /*<<< orphan*/ *) ; 
 scalar_t__ kadm5_log_nop (int /*<<< orphan*/ *) ; 
 scalar_t__ kadm5_log_reinit (int /*<<< orphan*/ *) ; 
 scalar_t__ kadm5_log_set_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kadm5_ret_t
kadm5_log_truncate (kadm5_server_context *server_context)
{
    kadm5_ret_t ret;
    uint32_t vno;

    ret = kadm5_log_init (server_context);
    if (ret)
	return ret;

    ret = kadm5_log_get_version (server_context, &vno);
    if (ret)
	return ret;

    ret = kadm5_log_reinit (server_context);
    if (ret)
	return ret;

    ret = kadm5_log_set_version (server_context, vno);
    if (ret)
	return ret;

    ret = kadm5_log_nop (server_context);
    if (ret)
	return ret;

    ret = kadm5_log_end (server_context);
    if (ret)
	return ret;
    return 0;

}