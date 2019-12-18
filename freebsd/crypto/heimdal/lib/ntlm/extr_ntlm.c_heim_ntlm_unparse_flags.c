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
 int /*<<< orphan*/  ntlm_flag_units ; 
 size_t unparse_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 

size_t
heim_ntlm_unparse_flags(uint32_t flags, char *s, size_t len)
{
    return unparse_flags(flags, ntlm_flag_units, s, len);
}