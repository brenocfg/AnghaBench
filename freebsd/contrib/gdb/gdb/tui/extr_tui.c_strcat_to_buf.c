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
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 

void
strcat_to_buf (char *buf, int buflen, const char *item_to_add)
{
  if (item_to_add != (char *) NULL && buf != (char *) NULL)
    {
      if ((strlen (buf) + strlen (item_to_add)) <= buflen)
	strcat (buf, item_to_add);
      else
	strncat (buf, item_to_add, (buflen - strlen (buf)));
    }
}