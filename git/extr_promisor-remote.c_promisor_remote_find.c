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
struct promisor_remote {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  promisor_remote_init () ; 
 struct promisor_remote* promisor_remote_lookup (char const*,int /*<<< orphan*/ *) ; 
 struct promisor_remote* promisors ; 

struct promisor_remote *promisor_remote_find(const char *remote_name)
{
	promisor_remote_init();

	if (!remote_name)
		return promisors;

	return promisor_remote_lookup(remote_name, NULL);
}