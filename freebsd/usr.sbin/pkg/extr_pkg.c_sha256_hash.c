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

/* Variables and functions */
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 

__attribute__((used)) static void
sha256_hash(unsigned char hash[SHA256_DIGEST_LENGTH],
    char out[SHA256_DIGEST_LENGTH * 2 + 1])
{
	int i;

	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
		sprintf(out + (i * 2), "%02x", hash[i]);

	out[SHA256_DIGEST_LENGTH * 2] = '\0';
}