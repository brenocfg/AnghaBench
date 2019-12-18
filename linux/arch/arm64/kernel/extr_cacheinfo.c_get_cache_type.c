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
typedef  enum cache_type { ____Placeholder_cache_type } cache_type ;

/* Variables and functions */
 int CACHE_TYPE_NOCACHE ; 
 int CLIDR_CTYPE (int /*<<< orphan*/ ,int) ; 
 int MAX_CACHE_LEVEL ; 
 int /*<<< orphan*/  clidr_el1 ; 
 int /*<<< orphan*/  read_sysreg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum cache_type get_cache_type(int level)
{
	u64 clidr;

	if (level > MAX_CACHE_LEVEL)
		return CACHE_TYPE_NOCACHE;
	clidr = read_sysreg(clidr_el1);
	return CLIDR_CTYPE(clidr, level);
}