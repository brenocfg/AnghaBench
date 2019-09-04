#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_socket_t ;
struct TYPE_3__ {unsigned int cur; int ret; int /*<<< orphan*/  call_cnt; } ;
struct TYPE_4__ {TYPE_1__ minimize_notsent_lowat; } ;

/* Variables and functions */
 TYPE_2__ cb_ret_vars ; 

__attribute__((used)) static int test_adjust_notsent_lowat(h2o_socket_t *sock, unsigned notsent_lowat)
{
    cb_ret_vars.minimize_notsent_lowat.cur = notsent_lowat;
    ++cb_ret_vars.minimize_notsent_lowat.call_cnt;
    return cb_ret_vars.minimize_notsent_lowat.ret;
}