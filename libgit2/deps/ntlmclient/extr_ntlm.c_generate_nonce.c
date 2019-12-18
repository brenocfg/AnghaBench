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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {scalar_t__ nonce; } ;
typedef  TYPE_1__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__*,unsigned char*,int) ; 
 int /*<<< orphan*/  ntlm_random_bytes (TYPE_1__*,unsigned char*,int) ; 

__attribute__((used)) static bool generate_nonce(ntlm_client *ntlm)
{
	unsigned char buf[8];

	if (ntlm->nonce)
		return true;

	if (!ntlm_random_bytes(ntlm, buf, 8))
		return false;

	memcpy(&ntlm->nonce, buf, sizeof(uint64_t));
	return true;
}