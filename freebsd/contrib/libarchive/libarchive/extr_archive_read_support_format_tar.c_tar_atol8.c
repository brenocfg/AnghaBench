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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  tar_atol_base_n (char const*,size_t,int) ; 

__attribute__((used)) static int64_t
tar_atol8(const char *p, size_t char_cnt)
{
	return tar_atol_base_n(p, char_cnt, 8);
}