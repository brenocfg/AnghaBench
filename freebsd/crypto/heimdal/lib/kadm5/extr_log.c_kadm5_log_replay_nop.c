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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  kadm5_server_context ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;

/* Variables and functions */

__attribute__((used)) static kadm5_ret_t
kadm5_log_replay_nop (kadm5_server_context *context,
		      uint32_t ver,
		      uint32_t len,
		      krb5_storage *sp)
{
    return 0;
}