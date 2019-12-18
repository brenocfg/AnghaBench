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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  XXH64 (char const*,size_t const,int /*<<< orphan*/  const) ; 

void brain_client_generate_hash (u64 *hash, const char *line_buf, const size_t line_len)
{
  const u64 seed = 0;

  hash[0] = XXH64 (line_buf, line_len, seed);
}