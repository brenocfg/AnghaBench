#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* shared_dir; } ;
typedef  TYPE_1__ folder_config_t ;

/* Variables and functions */
 int snprintf (char*,size_t const,char*,char*,int const) ; 

int module_filename (const folder_config_t *folder_config, const int hash_mode, char *out_buf, const size_t out_size)
{
  // native compiled
  #if defined (_WIN) || defined (__CYGWIN__)
  return snprintf (out_buf, out_size, "%s/modules/module_%05d.dll", folder_config->shared_dir, hash_mode);
  #else
  return snprintf (out_buf, out_size, "%s/modules/module_%05d.so", folder_config->shared_dir, hash_mode);
  #endif
}