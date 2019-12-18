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
struct evutil_addrinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_dns_callback (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
getaddrinfo_cb(int err, struct evutil_addrinfo *res, void *ptr)
{
	generic_dns_callback(err, 0, 0, 0, NULL, ptr);
}