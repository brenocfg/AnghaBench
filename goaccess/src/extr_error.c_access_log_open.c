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
 int /*<<< orphan*/  F_OK ; 
 int access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * access_log ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 

int
access_log_open (const char *path)
{
  if (path == NULL)
    return 0;

  if (access (path, F_OK) != -1)
    access_log = fopen (path, "a");
  else
    access_log = fopen (path, "w");
  if (access_log == NULL)
    return 1;

  return 0;
}