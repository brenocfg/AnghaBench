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
struct TYPE_3__ {char const* errmsg; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  NTLM_STATE_ERROR ; 

void ntlm_client_set_errmsg(ntlm_client *ntlm, const char *errmsg)
{
	ntlm->state = NTLM_STATE_ERROR;
	ntlm->errmsg = errmsg;
}