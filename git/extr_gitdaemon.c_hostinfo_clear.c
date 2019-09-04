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
struct hostinfo {int /*<<< orphan*/  tcp_port; int /*<<< orphan*/  ip_address; int /*<<< orphan*/  canon_hostname; int /*<<< orphan*/  hostname; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hostinfo_clear(struct hostinfo *hi)
{
	strbuf_release(&hi->hostname);
	strbuf_release(&hi->canon_hostname);
	strbuf_release(&hi->ip_address);
	strbuf_release(&hi->tcp_port);
}