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
typedef  int /*<<< orphan*/  var ;
struct TYPE_3__ {int Revision; } ;
struct TYPE_4__ {TYPE_1__ Hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_VOLATILE ; 
 TYPE_2__* ST ; 
 int /*<<< orphan*/  env_noset ; 
 int /*<<< orphan*/  env_nounset ; 
 int /*<<< orphan*/  env_setenv (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

void
efi_init_environment(void)
{
	char var[128];

	snprintf(var, sizeof(var), "%d.%02d", ST->Hdr.Revision >> 16,
	    ST->Hdr.Revision & 0xffff);
	env_setenv("efi-version", EV_VOLATILE, var, env_noset, env_nounset);
}