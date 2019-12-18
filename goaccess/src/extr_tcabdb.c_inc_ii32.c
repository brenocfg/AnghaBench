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
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 scalar_t__ tcadbaddint (void*,int*,int,int) ; 

__attribute__((used)) static int
inc_ii32 (void *hash, int key, int inc)
{
  if (!hash)
    return -1;

  /* if key exists in the database, it is incremented */
  if (tcadbaddint (hash, &key, sizeof (int), inc) == INT_MIN)
    LOG_DEBUG (("Unable to tcadbput\n"));

  return 0;
}