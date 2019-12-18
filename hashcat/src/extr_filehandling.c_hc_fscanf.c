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
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 scalar_t__ HCBUFSIZ_TINY ; 
 char* hc_fgets (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (scalar_t__) ; 
 int /*<<< orphan*/  sscanf (char*,char const*,void*) ; 

int hc_fscanf (HCFILE *fp, const char *format, void *ptr)
{
  if (fp == NULL) return -1;

  char *buf = (char *) hcmalloc (HCBUFSIZ_TINY);

  if (buf == NULL) return -1;

  char *b = hc_fgets (buf, HCBUFSIZ_TINY - 1, fp);

  if (b == NULL)
  {
    hcfree (buf);

    return -1;
  }

  sscanf (b, format, ptr);

  hcfree (buf);

  return 1;
}