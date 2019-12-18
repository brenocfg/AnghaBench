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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  pkg_atol256 (char const*,unsigned int) ; 
 int /*<<< orphan*/  pkg_atol8 (char const*,unsigned int) ; 

__attribute__((used)) static off_t
pkg_atol(const char *p, unsigned char_cnt)
{
	/*
	 * Technically, GNU pkg considers a field to be in base-256
	 * only if the first byte is 0xff or 0x80.
	 */
	if (*p & 0x80)
		return (pkg_atol256(p, char_cnt));
	return (pkg_atol8(p, char_cnt));
}