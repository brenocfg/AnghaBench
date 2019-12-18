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
 char* MSG_ENOMEM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t const) ; 
 void* realloc (void*,size_t const) ; 
 int /*<<< orphan*/  stderr ; 

void *hcrealloc (void *ptr, const size_t oldsz, const size_t addsz)
{
  void *p = realloc (ptr, oldsz + addsz);

  if (p == NULL)
  {
    fprintf (stderr, "%s\n", MSG_ENOMEM);

    return (NULL);
  }

  memset ((char *) p + oldsz, 0, addsz);

  return (p);
}