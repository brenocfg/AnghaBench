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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_bzclose (scalar_t__) ; 
 scalar_t__ BZflag ; 
#define  EACCES 129 
 int EINTR ; 
#define  EISDIR 128 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 scalar_t__ RECURSE_DIRECTORIES ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SET_BINARY (int) ; 
 scalar_t__ SKIP_DIRECTORIES ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ Zflag ; 
 char* _ (char*) ; 
 scalar_t__ after_last_match ; 
 scalar_t__ bufmapped ; 
 scalar_t__ bufoffset ; 
 scalar_t__ bzbufdesc ; 
 scalar_t__ close (int) ; 
 scalar_t__ count_matches ; 
 scalar_t__ directories ; 
 int errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 char* filename ; 
 char filename_mask ; 
 int grep (int,char const*,struct stats*) ; 
 int grepdir (char const*,struct stats*) ; 
 int /*<<< orphan*/  gzbufdesc ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ ) ; 
 scalar_t__ is_EISDIR (int,char const*) ; 
 int /*<<< orphan*/  isatty (int) ; 
 int /*<<< orphan*/  isdir (char const*) ; 
 char* label ; 
 int list_files ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int open (char const*,int) ; 
 scalar_t__ out_file ; 
 scalar_t__ outleft ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ stat (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  suppress_errors ; 
 int /*<<< orphan*/  suppressible_error (char const*,int) ; 

__attribute__((used)) static int
grepfile (char const *file, struct stats *stats)
{
  int desc;
  int count;
  int status;
  int flags;

  if (! file)
    {
      desc = 0;
      filename = label ? label : _("(standard input)");
    }
  else
    {
      while ((desc = open (file, O_RDONLY | O_NONBLOCK)) < 0 && errno == EINTR)
	continue;

      if (desc < 0)
	{
	  int e = errno;

	  if (is_EISDIR (e, file) && directories == RECURSE_DIRECTORIES)
	    {
	      if (stat (file, &stats->stat) != 0)
		{
		  error (0, errno, "%s", file);
		  return 1;
		}

	      return grepdir (file, stats);
	    }

	  if (!suppress_errors)
	    {
	      if (directories == SKIP_DIRECTORIES)
		switch (e)
		  {
#if defined(EISDIR)
		  case EISDIR:
		    return 1;
#endif
		  case EACCES:
		    /* When skipping directories, don't worry about
		       directories that can't be opened.  */
		    if (isdir (file))
		      return 1;
		    break;
		  }
	    }

	  suppressible_error (file, e);
	  return 1;
	}

      flags = fcntl(desc, F_GETFL);
      flags &= ~O_NONBLOCK;
      fcntl(desc, F_SETFL, flags);
      filename = file;
    }

#if defined(SET_BINARY)
  /* Set input to binary mode.  Pipes are simulated with files
     on DOS, so this includes the case of "foo | grep bar".  */
  if (!isatty (desc))
    SET_BINARY (desc);
#endif

  count = grep (desc, file, stats);
  if (count < 0)
    status = count + 2;
  else
    {
      if (count_matches)
	{
	  if (out_file)
	    printf ("%s%c", filename, ':' & filename_mask);
	  printf ("%d\n", count);
	}

      status = !count;
      if (list_files == 1 - 2 * status)
	printf ("%s%c", filename, '\n' & filename_mask);

      if (BZflag && bzbufdesc)
	BZ2_bzclose(bzbufdesc);
      else
#if HAVE_LIBZ > 0
      if (Zflag)
	gzclose(gzbufdesc);
      else
#endif
      if (! file)
	{
	  off_t required_offset = outleft ? bufoffset : after_last_match;
	  if ((bufmapped || required_offset != bufoffset)
	      && lseek (desc, required_offset, SEEK_SET) < 0
	      && S_ISREG (stats->stat.st_mode))
	    error (0, errno, "%s", filename);
	}
      else
	while (close (desc) != 0)
	  if (errno != EINTR)
	    {
	      error (0, errno, "%s", file);
	      break;
	    }
    }

  return status;
}