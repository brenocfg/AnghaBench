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
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 int at_mark (char const*,int,char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int push_mark(const char *string, int len)
{
	const char *suffix[] = { "@{push}" };
	return at_mark(string, len, suffix, ARRAY_SIZE(suffix));
}