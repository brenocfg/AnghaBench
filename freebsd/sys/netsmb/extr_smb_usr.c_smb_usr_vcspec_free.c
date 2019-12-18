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
struct smb_vcspec {scalar_t__ lap; scalar_t__ sap; } ;

/* Variables and functions */
 int /*<<< orphan*/  smb_memfree (scalar_t__) ; 

__attribute__((used)) static void
smb_usr_vcspec_free(struct smb_vcspec *spec)
{
	if (spec->sap)
		smb_memfree(spec->sap);
	if (spec->lap)
		smb_memfree(spec->lap);
}