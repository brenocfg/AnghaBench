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
typedef  int /*<<< orphan*/  kadm5_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  __CALL (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  flush ; 

kadm5_ret_t
kadm5_flush (void *server_handle)
{
    return __CALL(flush, (server_handle));
}