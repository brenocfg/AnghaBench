#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pfp; scalar_t__ is_zip; int /*<<< orphan*/  gfp; scalar_t__ is_gzip; } ;
typedef  TYPE_1__ HCFILE ;

/* Variables and functions */
 size_t fwrite (void const*,size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t gzfwrite (void const*,size_t,size_t,int /*<<< orphan*/ ) ; 

size_t hc_fwrite (const void *ptr, size_t size, size_t nmemb, HCFILE *fp)
{
  size_t n = -1;

  if (fp == NULL) return n;

  if (fp->is_gzip)
  {
    n = gzfwrite (ptr, size, nmemb, fp->gfp);
  }
  else if (fp->is_zip)
  {
  }
  else
  {
    n = fwrite (ptr, size, nmemb, fp->pfp);
  }

  if (n != nmemb) return -1;

  return n;
}