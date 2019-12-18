#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t af_filesz; } ;
typedef  TYPE_1__ au_fstat_t ;
typedef  int /*<<< orphan*/  au_fstat ;

/* Variables and functions */
 int ADE_AUDITON ; 
 int ADE_NOERR ; 
 int ADE_PARSE ; 
 scalar_t__ audit_set_fsize (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 scalar_t__ getacfilesz (size_t*) ; 

int
auditd_set_fsize(void)
{
	size_t filesz;
	au_fstat_t au_fstat;

	/*
	 * Set trail rotation size.
	 */
	if (getacfilesz(&filesz) != 0)
		return (ADE_PARSE);

	bzero(&au_fstat, sizeof(au_fstat));
	au_fstat.af_filesz = filesz;
	if (audit_set_fsize(&au_fstat, sizeof(au_fstat)) != 0)
		return (ADE_AUDITON);

	return (ADE_NOERR);
}