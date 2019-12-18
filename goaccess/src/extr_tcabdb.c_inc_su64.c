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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 void* tcadbget (void*,char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tcadbput (void*,char const*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int
inc_su64 (void *hash, const char *key, uint64_t inc)
{
  int sp;
  uint64_t value = inc;
  void *ptr;

  if (!hash)
    return -1;

  if ((ptr = tcadbget (hash, key, strlen (key), &sp)) != NULL) {
    value = (*(uint64_t *) ptr) + inc;
    free (ptr);
  }

  /* if key exists in the database, it is overwritten */
  if (!tcadbput (hash, key, strlen (key), &value, sizeof (uint64_t)))
    LOG_DEBUG (("Unable to tcadbput\n"));

  return 0;
}