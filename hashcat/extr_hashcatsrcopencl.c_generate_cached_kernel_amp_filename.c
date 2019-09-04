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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int const,char const*) ; 

void generate_cached_kernel_amp_filename (const u32 attack_kern, char *profile_dir, const char *device_name_chksum_amp_mp, char *cached_file)
{
  snprintf (cached_file, 255, "%s/kernels/amp_a%u.%s.kernel", profile_dir, attack_kern, device_name_chksum_amp_mp);
}