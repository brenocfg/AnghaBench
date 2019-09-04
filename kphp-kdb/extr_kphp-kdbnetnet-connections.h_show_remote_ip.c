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
struct connection {int /*<<< orphan*/  remote_ipv6; int /*<<< orphan*/  remote_ip; } ;

/* Variables and functions */
 char* show_ip46 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *show_remote_ip (struct connection *c) { return show_ip46 (c->remote_ip, c->remote_ipv6); }