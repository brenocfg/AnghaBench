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
typedef  int /*<<< orphan*/  wc_Sha256 ;
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  wc_InitSha256 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wc_Sha256Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wc_Sha256Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 

int sha256_vector(size_t num_elem, const u8 *addr[], const size_t *len,
		  u8 *mac)
{
	wc_Sha256 sha256;
	size_t i;

	if (TEST_FAIL())
		return -1;

	wc_InitSha256(&sha256);

	for (i = 0; i < num_elem; i++)
		wc_Sha256Update(&sha256, addr[i], len[i]);

	wc_Sha256Final(&sha256, mac);

	return 0;
}