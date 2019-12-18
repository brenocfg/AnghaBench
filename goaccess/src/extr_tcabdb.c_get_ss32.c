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
 char* tcadbget2 (void*,char const*) ; 

__attribute__((used)) static char *
get_ss32 (void *hash, const char *key)
{
  char *value = NULL;

  if (!hash)
    return NULL;

  if ((value = tcadbget2 (hash, key)) != NULL)
    return value;

  return NULL;
}