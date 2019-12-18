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
struct TYPE_4__ {int /*<<< orphan*/  pr_hostname; } ;
struct TYPE_3__ {int /*<<< orphan*/  version; int /*<<< orphan*/  release; int /*<<< orphan*/  nodename; int /*<<< orphan*/  sysname; } ;

/* Variables and functions */
 int osreldate ; 
 int /*<<< orphan*/  osrelease ; 
 int /*<<< orphan*/  ostype ; 
 TYPE_2__ prison0 ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 TYPE_1__ utsname ; 

__attribute__((used)) static void
opensolaris_utsname_init(void *arg)
{

	utsname.sysname = ostype;
	utsname.nodename = prison0.pr_hostname;
	utsname.release = osrelease;
	snprintf(utsname.version, sizeof(utsname.version), "%d", osreldate);
}