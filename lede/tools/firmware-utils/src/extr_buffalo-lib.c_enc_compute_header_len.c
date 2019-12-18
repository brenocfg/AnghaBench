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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 unsigned long ENC_MAGIC_LEN ; 
 unsigned long strlen (char*) ; 

unsigned long enc_compute_header_len(char *product, char *version)
{
	return ENC_MAGIC_LEN + 1 + strlen(product) + 1 +
	       strlen(version) + 1 + 3 * sizeof(uint32_t);
}