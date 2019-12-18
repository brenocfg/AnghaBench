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
 int /*<<< orphan*/  FATAL (char*) ; 
 void* calloc (size_t,size_t) ; 

void *
xcalloc (size_t nmemb, size_t size)
{
  void *ptr;

  if ((ptr = calloc (nmemb, size)) == NULL)
    FATAL ("Unable to calloc memory - failed.");

  return (ptr);
}