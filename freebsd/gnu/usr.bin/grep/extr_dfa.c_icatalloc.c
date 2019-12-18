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
 scalar_t__ malloc (size_t) ; 
 scalar_t__ realloc (void*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *
icatalloc (char *old, char *new)
{
  char *result;
  size_t oldsize, newsize;

  newsize = (new == NULL) ? 0 : strlen(new);
  if (old == NULL)
    oldsize = 0;
  else if (newsize == 0)
    return old;
  else	oldsize = strlen(old);
  if (old == NULL)
    result = (char *) malloc(newsize + 1);
  else
    result = (char *) realloc((void *) old, oldsize + newsize + 1);
  if (result != NULL && new != NULL)
    (void) strcpy(result + oldsize, new);
  return result;
}