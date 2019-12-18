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
struct nl_sock {int dummy; } ;
struct nl_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct nl_sock* __alloc_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_cb_get (struct nl_cb*) ; 

struct nl_sock *nl_socket_alloc_cb(struct nl_cb *cb)
{
	if (cb == NULL)
		BUG();

	return __alloc_socket(nl_cb_get(cb));
}