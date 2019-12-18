#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  st_mode; } ;
struct stats {TYPE_1__ stat; } ;

/* Variables and functions */
 void* ALIGN_TO (scalar_t__,int) ; 
 int /*<<< orphan*/ * BZ2_bzdopen (int,char*) ; 
 scalar_t__ BZflag ; 
 scalar_t__ INITIAL_BUFSIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ SKIP_DEVICES ; 
 scalar_t__ SKIP_DIRECTORIES ; 
 int STDIN_FILENO ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ Zflag ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 void* bufalloc ; 
 int /*<<< orphan*/ * bufbeg ; 
 int bufdesc ; 
 scalar_t__ buffer ; 
 int /*<<< orphan*/ * buflim ; 
 int bufmapped ; 
 int bufoffset ; 
 int /*<<< orphan*/ * bzbufdesc ; 
 scalar_t__ devices ; 
 scalar_t__ directories ; 
 int /*<<< orphan*/  eolbyte ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fstat (int,TYPE_1__*) ; 
 int getpagesize () ; 
 int /*<<< orphan*/ * gzbufdesc ; 
 int /*<<< orphan*/ * gzdopen (int,char*) ; 
 int initial_bufoffset ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmap_option ; 
 int pagesize ; 
 scalar_t__ xmalloc (void*) ; 

__attribute__((used)) static int
reset (int fd, char const *file, struct stats *stats)
{
  if (! pagesize)
    {
      pagesize = getpagesize ();
      if (pagesize == 0 || 2 * pagesize + 1 <= pagesize)
	abort ();
      bufalloc = ALIGN_TO (INITIAL_BUFSIZE, pagesize) + pagesize + 1;
      buffer = xmalloc (bufalloc);
    }
  if (BZflag)
    {
    bzbufdesc = BZ2_bzdopen(fd, "r");
    if (bzbufdesc == NULL)
      error(2, 0, _("memory exhausted"));
    }
#if HAVE_LIBZ > 0
  if (Zflag)
    {
    gzbufdesc = gzdopen(fd, "r");
    if (gzbufdesc == NULL)
      error(2, 0, _("memory exhausted"));
    }
#endif

  bufbeg = buflim = ALIGN_TO (buffer + 1, pagesize);
  bufbeg[-1] = eolbyte;
  bufdesc = fd;

  if (fstat (fd, &stats->stat) != 0)
    {
      error (0, errno, "fstat");
      return 0;
    }
  if (fd != STDIN_FILENO) {
    if (directories == SKIP_DIRECTORIES && S_ISDIR (stats->stat.st_mode))
      return 0;
#ifndef DJGPP
    if (devices == SKIP_DEVICES && (S_ISCHR(stats->stat.st_mode) || S_ISBLK(stats->stat.st_mode) || S_ISSOCK(stats->stat.st_mode) || S_ISFIFO(stats->stat.st_mode)))
#else
    if (devices == SKIP_DEVICES && (S_ISCHR(stats->stat.st_mode) || S_ISBLK(stats->stat.st_mode)))
#endif
      return 0;
  }
  if (
      BZflag ||
#if HAVE_LIBZ > 0
      Zflag ||
#endif
      S_ISREG (stats->stat.st_mode))
    {
      if (file)
	bufoffset = 0;
      else
	{
	  bufoffset = lseek (fd, 0, SEEK_CUR);
	  if (bufoffset < 0)
	    {
	      error (0, errno, "lseek");
	      return 0;
	    }
	}
#if defined(HAVE_MMAP)
      initial_bufoffset = bufoffset;
      bufmapped = mmap_option && bufoffset % pagesize == 0;
#endif
    }
  else
    {
#if defined(HAVE_MMAP)
      bufmapped = 0;
#endif
    }
  return 1;
}