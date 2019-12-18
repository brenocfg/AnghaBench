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
typedef  scalar_t__ gss_cred_usage_t ;

/* Variables and functions */
 int AUSAGE ; 
 scalar_t__ GSS_C_ACCEPT ; 
 scalar_t__ GSS_C_BOTH ; 
 scalar_t__ GSS_C_INITIATE ; 
 int IUSAGE ; 

__attribute__((used)) static void
updateusage(gss_cred_usage_t usage, int *usagemask)
{
    if (usage == GSS_C_BOTH)
	*usagemask |= AUSAGE | IUSAGE;
    else if (usage == GSS_C_ACCEPT)
	*usagemask |= AUSAGE;
    else if (usage == GSS_C_INITIATE)
	*usagemask |= IUSAGE;
}