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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  n ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strnlen (char const*,int) ; 

__attribute__((used)) static u64 make_field(const char *text, u64 index)
{
	u64 n = 0;

	memcpy((char *)&n, text, strnlen(text, sizeof(n)));
	return n + index;
}