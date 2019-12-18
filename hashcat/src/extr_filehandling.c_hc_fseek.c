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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int /*<<< orphan*/  pfp; scalar_t__ is_zip; int /*<<< orphan*/  gfp; scalar_t__ is_gzip; } ;
typedef  TYPE_1__ HCFILE ;

/* Variables and functions */
 int fseeko (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gzseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int hc_fseek (HCFILE *fp, off_t offset, int whence)
{
  int r = -1;

  if (fp == NULL) return r;

  if (fp->is_gzip)
  {
    r = gzseek (fp->gfp, offset, whence);
  }
  else if (fp->is_zip)
  {
    /*
    // untested and not used in wordlist engine
    zlib_filefunc64_32_def *d = NULL;
    if (whence == SEEK_SET)
    {
      r = ZSEEK64(*d, fp->ufp, offset, ZLIB_FILEFUNC_SEEK_SET);
    }
    else if (whence == SEEK_CUR)
    {
      r = ZSEEK64(*d, fp->ufp, offset, ZLIB_FILEFUNC_SEEK_CUR);
    }
    else if (whence == SEEK_END)
    {
      r = ZSEEK64(*d, fp->ufp, offset, ZLIB_FILEFUNC_SEEK_END);
    }
    // or
    // r = unzSetOffset (fp->ufp, offset);
    */
  }
  else
  {
    r = fseeko (fp->pfp, offset, whence);
  }

  return r;
}