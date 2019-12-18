#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  geoslot; int /*<<< orphan*/  chassis; } ;
typedef  TYPE_1__ unit_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcap_snprintf (char*,size_t,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nonUnified_IOP_port_name(char *buf, size_t bufsize, const char *proto, unit_t *u) {

	pcap_snprintf(buf, bufsize, "%s_%d_%d", proto, u->chassis, u->geoslot);
}