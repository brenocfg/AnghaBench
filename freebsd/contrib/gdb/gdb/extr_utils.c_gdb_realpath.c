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
 int MAXPATHLEN ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  _PC_PATH_MAX ; 
 char* alloca (long) ; 
 char* canonicalize_file_name (char const*) ; 
 long pathconf (char*,int /*<<< orphan*/ ) ; 
 void* realpath (char const*,char*) ; 
 char* xstrdup (char const*) ; 

char *
gdb_realpath (const char *filename)
{
  /* Method 1: The system has a compile time upper bound on a filename
     path.  Use that and realpath() to canonicalize the name.  This is
     the most common case.  Note that, if there isn't a compile time
     upper bound, you want to avoid realpath() at all costs.  */
#if defined(HAVE_REALPATH)
  {
# if defined (PATH_MAX)
    char buf[PATH_MAX];
#  define USE_REALPATH
# elif defined (MAXPATHLEN)
    char buf[MAXPATHLEN];
#  define USE_REALPATH
# endif
# if defined (USE_REALPATH)
    const char *rp = realpath (filename, buf);
    if (rp == NULL)
      rp = filename;
    return xstrdup (rp);
# endif
  }
#endif /* HAVE_REALPATH */

  /* Method 2: The host system (i.e., GNU) has the function
     canonicalize_file_name() which malloc's a chunk of memory and
     returns that, use that.  */
#if defined(HAVE_CANONICALIZE_FILE_NAME)
  {
    char *rp = canonicalize_file_name (filename);
    if (rp == NULL)
      return xstrdup (filename);
    else
      return rp;
  }
#endif

  /* FIXME: cagney/2002-11-13:

     Method 2a: Use realpath() with a NULL buffer.  Some systems, due
     to the problems described in in method 3, have modified their
     realpath() implementation so that it will allocate a buffer when
     NULL is passed in.  Before this can be used, though, some sort of
     configure time test would need to be added.  Otherwize the code
     will likely core dump.  */

  /* Method 3: Now we're getting desperate!  The system doesn't have a
     compile time buffer size and no alternative function.  Query the
     OS, using pathconf(), for the buffer limit.  Care is needed
     though, some systems do not limit PATH_MAX (return -1 for
     pathconf()) making it impossible to pass a correctly sized buffer
     to realpath() (it could always overflow).  On those systems, we
     skip this.  */
#if defined (HAVE_REALPATH) && defined (HAVE_UNISTD_H) && defined(HAVE_ALLOCA)
  {
    /* Find out the max path size.  */
    long path_max = pathconf ("/", _PC_PATH_MAX);
    if (path_max > 0)
      {
	/* PATH_MAX is bounded.  */
	char *buf = alloca (path_max);
	char *rp = realpath (filename, buf);
	return xstrdup (rp ? rp : filename);
      }
  }
#endif

  /* This system is a lost cause, just dup the buffer.  */
  return xstrdup (filename);
}