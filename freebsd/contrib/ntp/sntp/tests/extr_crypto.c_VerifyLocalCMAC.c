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
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_IGNORE_MESSAGE (char*) ; 

void
VerifyLocalCMAC(struct key *cmac)
{

	/* XXX: HMS: auth_md5 must be renamed/incorrect. */
	// TEST_ASSERT_TRUE(auth_md5(PKT_DATA, PKT_LEN, CMAC_LENGTH, cmac));

	TEST_IGNORE_MESSAGE("Hook in the local AES-128-CMAC check!");

	return;
}