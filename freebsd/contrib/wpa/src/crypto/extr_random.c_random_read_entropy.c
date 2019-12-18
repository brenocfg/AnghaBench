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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int RANDOM_ENTROPY_SIZE ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_readfile (int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ own_pool_ready ; 
 int /*<<< orphan*/  random_add_randomness (char*,int) ; 
 int /*<<< orphan*/  random_entropy_file ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void random_read_entropy(void)
{
	char *buf;
	size_t len;

	if (!random_entropy_file)
		return;

	buf = os_readfile(random_entropy_file, &len);
	if (buf == NULL)
		return; /* entropy file not yet available */

	if (len != 1 + RANDOM_ENTROPY_SIZE) {
		wpa_printf(MSG_DEBUG, "random: Invalid entropy file %s",
			   random_entropy_file);
		os_free(buf);
		return;
	}

	own_pool_ready = (u8) buf[0];
	random_add_randomness(buf + 1, RANDOM_ENTROPY_SIZE);
	os_free(buf);
	wpa_printf(MSG_DEBUG, "random: Added entropy from %s "
		   "(own_pool_ready=%u)",
		   random_entropy_file, own_pool_ready);
}