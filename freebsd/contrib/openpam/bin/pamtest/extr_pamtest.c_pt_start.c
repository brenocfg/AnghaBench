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
struct TYPE_3__ {int /*<<< orphan*/ * conv; } ;

/* Variables and functions */
 int PAM_SUCCESS ; 
 int /*<<< orphan*/  openpam_ttyconv ; 
 int pam_start (char const*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ pamc ; 
 int /*<<< orphan*/  pamh ; 
 int /*<<< orphan*/  pt_error (int,char*,char const*) ; 
 int /*<<< orphan*/  pt_verbose (char*,char const*,char const*) ; 

__attribute__((used)) static int
pt_start(const char *service, const char *user)
{
	int pame;

	pamc.conv = &openpam_ttyconv;
	pt_verbose("pam_start(%s, %s)", service, user);
	if ((pame = pam_start(service, user, &pamc, &pamh)) != PAM_SUCCESS)
		pt_error(pame, "pam_start(%s)", service);
	return (pame);
}