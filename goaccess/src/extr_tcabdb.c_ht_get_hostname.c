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
 char* get_ss32 (void*,char const*) ; 
 void* ht_hostnames ; 

char *
ht_get_hostname (const char *host)
{
  void *hash = ht_hostnames;

  if (!hash)
    return NULL;

  return get_ss32 (hash, host);
}