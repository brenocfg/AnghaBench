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
 int EXACT ; 
 int NOMATCH ; 
 int PARTIAL ; 
 int /*<<< orphan*/  SKIP_SPACE (unsigned char const*) ; 
 scalar_t__ toupper (unsigned char const) ; 

__attribute__((used)) static int
Compare(const unsigned char *s, const unsigned char *buf,
	bool ccase)
{
  SKIP_SPACE(buf);		/* Skip leading spaces in both texts */
  SKIP_SPACE(s);

  if (*buf == '\0')
    {
      return (((*s) != '\0') ? NOMATCH : EXACT);
    }
  else
    {
      if (ccase)
	{
	  while (*s++ == *buf)
	    {
	      if (*buf++ == '\0')
		return EXACT;
	    }
	}
      else
	{
	  while (toupper(*s++) == toupper(*buf))
	    {
	      if (*buf++ == '\0')
		return EXACT;
	    }
	}
    }
  /* At this location buf points to the first character where it no longer
     matches with s. So if only blanks are following, we have a partial
     match otherwise there is no match */
  SKIP_SPACE(buf);
  if (*buf)
    return NOMATCH;

  /* If it happens that the reference buffer is at its end, the partial
     match is actually an exact match. */
  return ((s[-1] != '\0') ? PARTIAL : EXACT);
}