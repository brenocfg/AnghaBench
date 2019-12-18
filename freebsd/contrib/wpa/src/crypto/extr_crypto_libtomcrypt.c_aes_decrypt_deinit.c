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
typedef  int /*<<< orphan*/  symmetric_key ;

/* Variables and functions */
 int /*<<< orphan*/  aes_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

void aes_decrypt_deinit(void *ctx)
{
	symmetric_key *skey = ctx;
	aes_done(skey);
	os_free(skey);
}