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
 int DAX_HASH_SIZE ; 
 int hashlen_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashlen_string (char*,char const*) ; 

__attribute__((used)) static int dax_host_hash(const char *host)
{
	return hashlen_hash(hashlen_string("DAX", host)) % DAX_HASH_SIZE;
}