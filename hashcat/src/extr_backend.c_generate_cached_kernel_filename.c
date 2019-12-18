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
 int const ATTACK_EXEC_INSIDE_KERNEL ; 
 int const ATTACK_KERN_BF ; 
 int const ATTACK_KERN_COMBI ; 
 int const ATTACK_KERN_NONE ; 
 int const ATTACK_KERN_STRAIGHT ; 
 int const OPTI_TYPE_OPTIMIZED_KERNEL ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,char const*) ; 

void generate_cached_kernel_filename (const bool slow_candidates, const u32 attack_exec, const u32 attack_kern, const u32 kern_type, const u32 opti_type, char *profile_dir, const char *device_name_chksum, char *cached_file)
{
  if (opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
  {
    if (attack_exec == ATTACK_EXEC_INSIDE_KERNEL)
    {
      if (slow_candidates == true)
      {
        snprintf (cached_file, 255, "%s/kernels/m%05d_a0-optimized.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
      }
      else
      {
        if (attack_kern == ATTACK_KERN_STRAIGHT)
          snprintf (cached_file, 255, "%s/kernels/m%05d_a0-optimized.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
        else if (attack_kern == ATTACK_KERN_COMBI)
          snprintf (cached_file, 255, "%s/kernels/m%05d_a1-optimized.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
        else if (attack_kern == ATTACK_KERN_BF)
          snprintf (cached_file, 255, "%s/kernels/m%05d_a3-optimized.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
        else if (attack_kern == ATTACK_KERN_NONE)
          snprintf (cached_file, 255, "%s/kernels/m%05d_a0-optimized.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
      }
    }
    else
    {
      snprintf (cached_file, 255, "%s/kernels/m%05d-optimized.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
    }
  }
  else
  {
    if (attack_exec == ATTACK_EXEC_INSIDE_KERNEL)
    {
      if (slow_candidates == true)
      {
        snprintf (cached_file, 255, "%s/kernels/m%05d_a0-pure.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
      }
      else
      {
        if (attack_kern == ATTACK_KERN_STRAIGHT)
          snprintf (cached_file, 255, "%s/kernels/m%05d_a0-pure.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
        else if (attack_kern == ATTACK_KERN_COMBI)
          snprintf (cached_file, 255, "%s/kernels/m%05d_a1-pure.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
        else if (attack_kern == ATTACK_KERN_BF)
          snprintf (cached_file, 255, "%s/kernels/m%05d_a3-pure.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
        else if (attack_kern == ATTACK_KERN_NONE)
          snprintf (cached_file, 255, "%s/kernels/m%05d_a0-pure.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
      }
    }
    else
    {
      snprintf (cached_file, 255, "%s/kernels/m%05d-pure.%s.kernel", profile_dir, (int) kern_type, device_name_chksum);
    }
  }
}