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
struct TYPE_3__ {int /*<<< orphan*/  pfp; int /*<<< orphan*/  ufp; scalar_t__ is_zip; int /*<<< orphan*/  gfp; scalar_t__ is_gzip; } ;
typedef  TYPE_1__ HCFILE ;

/* Variables and functions */
 size_t fread (void*,size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t gzfread (void*,size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t unzReadCurrentFile (int /*<<< orphan*/ ,void*,unsigned int) ; 

size_t hc_fread (void *ptr, size_t size, size_t nmemb, HCFILE *fp)
{
  size_t n = -1;

  if (fp == NULL) return n;

  if (fp->is_gzip)
  {
    n = gzfread (ptr, size, nmemb, fp->gfp);
  }
  else if (fp->is_zip)
  {
    unsigned s = size * nmemb;

    n = unzReadCurrentFile (fp->ufp, ptr, s);
  }
  else
  {
    n = fread (ptr, size, nmemb, fp->pfp);
  }

  return n;
}