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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

__attribute__((used)) static int
pbkdf2_sha1(const char *pw, size_t pw_len, const uint8_t *salt,
    size_t salt_len, unsigned rounds, uint8_t *derived_key,
    size_t derived_key_len) {
	(void)pw; /* UNUSED */
	(void)pw_len; /* UNUSED */
	(void)salt; /* UNUSED */
	(void)salt_len; /* UNUSED */
	(void)rounds; /* UNUSED */
	(void)derived_key; /* UNUSED */
	(void)derived_key_len; /* UNUSED */
	return -1; /* UNSUPPORTED */
}