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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ errno ; 
 int /*<<< orphan*/  strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
BN_hex2bn(BIGNUM **a, const char *str)
{
	char *p;

	errno = 0;
	**a = strtoul(str, &p, 16);
	return (errno == 0 && (*p == '\n' || *p == '\0'));
}