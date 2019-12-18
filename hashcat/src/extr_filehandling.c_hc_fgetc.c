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
 int fgetc (int /*<<< orphan*/ ) ; 
 int gzgetc (int /*<<< orphan*/ ) ; 
 int unzReadCurrentFile (int /*<<< orphan*/ ,unsigned char*,int) ; 

int hc_fgetc (HCFILE *fp)
{
  int r = -1;

  if (fp == NULL) return r;

  if (fp->is_gzip)
  {
    r = gzgetc (fp->gfp);
  }
  else if (fp->is_zip)
  {
    unsigned char c = 0;

    if (unzReadCurrentFile (fp->ufp, &c, 1) == 1) r = (int) c;
  }
  else
  {
    r = fgetc (fp->pfp);
  }

  return r;
}