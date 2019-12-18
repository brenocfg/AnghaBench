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
 int /*<<< orphan*/  memset (struct hostinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostinfo_init(struct hostinfo *hi)
{
	memset(hi, 0, sizeof(*hi));
	strbuf_init(&hi->hostname, 0);
	strbuf_init(&hi->canon_hostname, 0);
	strbuf_init(&hi->ip_address, 0);
	strbuf_init(&hi->tcp_port, 0);
}