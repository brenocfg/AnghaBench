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
struct mbdata {int dummy; } ;

/* Variables and functions */
 int smb_rq_dmem (struct mbdata*,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

int
smb_rq_dstring(struct mbdata *mbp, char *s)
{
	return smb_rq_dmem(mbp, s, strlen(s) + 1);
}