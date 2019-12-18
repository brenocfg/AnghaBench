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
struct TYPE_2__ {int /*<<< orphan*/  (* send_signal ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PBUFSIZ ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  remote_desc ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* the_target ; 
 void* tohex (unsigned char) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int
putpkt (char *buf)
{
  int i;
  unsigned char csum = 0;
  char *buf2;
  char buf3[1];
  int cnt = strlen (buf);
  char *p;

  buf2 = malloc (PBUFSIZ);

  /* Copy the packet into buffer BUF2, encapsulating it
     and giving it a checksum.  */

  p = buf2;
  *p++ = '$';

  for (i = 0; i < cnt; i++)
    {
      csum += buf[i];
      *p++ = buf[i];
    }
  *p++ = '#';
  *p++ = tohex ((csum >> 4) & 0xf);
  *p++ = tohex (csum & 0xf);

  *p = '\0';

  /* Send it over and over until we get a positive ack.  */

  do
    {
      int cc;

      if (write (remote_desc, buf2, p - buf2) != p - buf2)
	{
	  perror ("putpkt(write)");
	  return -1;
	}

      if (remote_debug)
	{
	  fprintf (stderr, "putpkt (\"%s\"); [looking for ack]\n", buf2);
	  fflush (stderr);
	}
      cc = read (remote_desc, buf3, 1);
      if (remote_debug)
	{
	  fprintf (stderr, "[received '%c' (0x%x)]\n", buf3[0], buf3[0]);
	  fflush (stderr);
	}

      if (cc <= 0)
	{
	  if (cc == 0)
	    fprintf (stderr, "putpkt(read): Got EOF\n");
	  else
	    perror ("putpkt(read)");

	  free (buf2);
	  return -1;
	}

      /* Check for an input interrupt while we're here.  */
      if (buf3[0] == '\003')
	(*the_target->send_signal) (SIGINT);
    }
  while (buf3[0] != '+');

  free (buf2);
  return 1;			/* Success! */
}