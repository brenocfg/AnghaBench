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
struct iwi_fw {TYPE_1__* fp; } ;
struct TYPE_2__ {int version; } ;

/* Variables and functions */
 void* firmware_get (char const*) ; 

__attribute__((used)) static void
iwi_getfw(struct iwi_fw *fw, const char *fwname,
	  struct iwi_fw *uc, const char *ucname)
{
	if (fw->fp == NULL)
		fw->fp = firmware_get(fwname);
	/* NB: pre-3.0 ucode is packaged separately */
	if (uc->fp == NULL && fw->fp != NULL && fw->fp->version < 300)
		uc->fp = firmware_get(ucname);
}