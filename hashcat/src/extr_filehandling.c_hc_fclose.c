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
struct TYPE_3__ {int is_gzip; int is_zip; int fd; int /*<<< orphan*/ * mode; int /*<<< orphan*/ * path; int /*<<< orphan*/ * pfp; int /*<<< orphan*/  ufp; int /*<<< orphan*/  gfp; } ;
typedef  TYPE_1__ HCFILE ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unzClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unzCloseCurrentFile (int /*<<< orphan*/ ) ; 

void hc_fclose (HCFILE *fp)
{
  if (fp == NULL) return;

  if (fp->is_gzip)
  {
    gzclose (fp->gfp);
  }
  else if (fp->is_zip)
  {
    unzCloseCurrentFile (fp->ufp);

    unzClose (fp->ufp);
  }
  else
  {
    fclose (fp->pfp);
  }

  close (fp->fd);

  fp->fd = -1;
  fp->pfp = NULL;
  fp->is_gzip = false;
  fp->is_zip = false;

  fp->path = NULL;
  fp->mode = NULL;
}