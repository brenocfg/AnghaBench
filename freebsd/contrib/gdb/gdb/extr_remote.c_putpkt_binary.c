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
struct remote_state {long remote_packet_size; } ;

/* Variables and functions */
#define  SERIAL_TIMEOUT 128 
 char* alloca (long) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputc_unfiltered (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputstrn_unfiltered (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  interrupt_query () ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  putchar_unfiltered (char) ; 
 scalar_t__ quit_flag ; 
 int /*<<< orphan*/  read_frame (char*,long) ; 
 int readchar (int /*<<< orphan*/ ) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  remote_desc ; 
 int /*<<< orphan*/  remote_timeout ; 
 scalar_t__ serial_write (int /*<<< orphan*/ ,char*,int) ; 
 void* tohex (unsigned char) ; 

__attribute__((used)) static int
putpkt_binary (char *buf, int cnt)
{
  struct remote_state *rs = get_remote_state ();
  int i;
  unsigned char csum = 0;
  char *buf2 = alloca (cnt + 6);
  long sizeof_junkbuf = (rs->remote_packet_size);
  char *junkbuf = alloca (sizeof_junkbuf);

  int ch;
  int tcount = 0;
  char *p;

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

  /* Send it over and over until we get a positive ack.  */

  while (1)
    {
      int started_error_output = 0;

      if (remote_debug)
	{
	  *p = '\0';
	  fprintf_unfiltered (gdb_stdlog, "Sending packet: ");
	  fputstrn_unfiltered (buf2, p - buf2, 0, gdb_stdlog);
	  fprintf_unfiltered (gdb_stdlog, "...");
	  gdb_flush (gdb_stdlog);
	}
      if (serial_write (remote_desc, buf2, p - buf2))
	perror_with_name ("putpkt: write failed");

      /* read until either a timeout occurs (-2) or '+' is read */
      while (1)
	{
	  ch = readchar (remote_timeout);

	  if (remote_debug)
	    {
	      switch (ch)
		{
		case '+':
		case '-':
		case SERIAL_TIMEOUT:
		case '$':
		  if (started_error_output)
		    {
		      putchar_unfiltered ('\n');
		      started_error_output = 0;
		    }
		}
	    }

	  switch (ch)
	    {
	    case '+':
	      if (remote_debug)
		fprintf_unfiltered (gdb_stdlog, "Ack\n");
	      return 1;
	    case '-':
	      if (remote_debug)
		fprintf_unfiltered (gdb_stdlog, "Nak\n");
	    case SERIAL_TIMEOUT:
	      tcount++;
	      if (tcount > 3)
		return 0;
	      break;		/* Retransmit buffer */
	    case '$':
	      {
	        if (remote_debug)
		  fprintf_unfiltered (gdb_stdlog, "Packet instead of Ack, ignoring it\n");
		/* It's probably an old response, and we're out of sync.
		   Just gobble up the packet and ignore it.  */
		read_frame (junkbuf, sizeof_junkbuf);
		continue;	/* Now, go look for + */
	      }
	    default:
	      if (remote_debug)
		{
		  if (!started_error_output)
		    {
		      started_error_output = 1;
		      fprintf_unfiltered (gdb_stdlog, "putpkt: Junk: ");
		    }
		  fputc_unfiltered (ch & 0177, gdb_stdlog);
		}
	      continue;
	    }
	  break;		/* Here to retransmit */
	}

#if 0
      /* This is wrong.  If doing a long backtrace, the user should be
         able to get out next time we call QUIT, without anything as
         violent as interrupt_query.  If we want to provide a way out of
         here without getting to the next QUIT, it should be based on
         hitting ^C twice as in remote_wait.  */
      if (quit_flag)
	{
	  quit_flag = 0;
	  interrupt_query ();
	}
#endif
    }
}