#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ at_type; } ;
struct auditinfo_addr {TYPE_1__ ai_termid; } ;

/* Variables and functions */
 scalar_t__ AU_IPv4 ; 
 scalar_t__ AU_IPv6 ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KINFO_WLOCK () ; 
 int /*<<< orphan*/  KINFO_WUNLOCK () ; 
 struct auditinfo_addr audit_kinfo ; 

void
audit_set_kinfo(struct auditinfo_addr *ak)
{

	KASSERT(ak->ai_termid.at_type == AU_IPv4 ||
	    ak->ai_termid.at_type == AU_IPv6,
	    ("audit_set_kinfo: invalid address type"));

	KINFO_WLOCK();
	audit_kinfo = *ak;
	KINFO_WUNLOCK();
}