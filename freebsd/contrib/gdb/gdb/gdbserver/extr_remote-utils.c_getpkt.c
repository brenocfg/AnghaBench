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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 unsigned char fromhex (int) ; 
 int readchar () ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  remote_desc ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

int
getpkt (char *buf)
{
  char *bp;
  unsigned char csum, c1, c2;
  int c;

  while (1)
    {
      csum = 0;

      while (1)
	{
	  c = readchar ();
	  if (c == '$')
	    break;
	  if (remote_debug)
	    {
	      fprintf (stderr, "[getpkt: discarding char '%c']\n", c);
	      fflush (stderr);
	    }

	  if (c < 0)
	    return -1;
	}

      bp = buf;
      while (1)
	{
	  c = readchar ();
	  if (c < 0)
	    return -1;
	  if (c == '#')
	    break;
	  *bp++ = c;
	  csum += c;
	}
      *bp = 0;

      c1 = fromhex (readchar ());
      c2 = fromhex (readchar ());

      if (csum == (c1 << 4) + c2)
	break;

      fprintf (stderr, "Bad checksum, sentsum=0x%x, csum=0x%x, buf=%s\n",
	       (c1 << 4) + c2, csum, buf);
      write (remote_desc, "-", 1);
    }

  if (remote_debug)
    {
      fprintf (stderr, "getpkt (\"%s\");  [sending ack] \n", buf);
      fflush (stderr);
    }

  write (remote_desc, "+", 1);

  if (remote_debug)
    {
      fprintf (stderr, "[sent ack]\n");
      fflush (stderr);
    }

  return bp - buf;
}