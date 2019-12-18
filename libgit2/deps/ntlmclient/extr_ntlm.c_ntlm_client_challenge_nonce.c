#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  nonce; } ;
struct TYPE_5__ {TYPE_1__ challenge; } ;
typedef  TYPE_2__ ntlm_client ;

/* Variables and functions */

uint64_t ntlm_client_challenge_nonce(ntlm_client *ntlm)
{
	return ntlm->challenge.nonce;
}