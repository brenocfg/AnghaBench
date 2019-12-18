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
struct ui_file {int dummy; } ;
struct remote_state {int remote_packet_size; } ;

/* Variables and functions */
 char* alloca (int) ; 
 int /*<<< orphan*/  bin2hex (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fputc_unfiltered (char,struct ui_file*) ; 
 int fromhex (char) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ putpkt (char*) ; 
 int /*<<< orphan*/  remote_console_output (char*) ; 
 int /*<<< orphan*/  remote_desc ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
remote_rcmd (char *command,
	     struct ui_file *outbuf)
{
  struct remote_state *rs = get_remote_state ();
  int i;
  char *buf = alloca (rs->remote_packet_size);
  char *p = buf;

  if (!remote_desc)
    error ("remote rcmd is only available after target open");

  /* Send a NULL command across as an empty command */
  if (command == NULL)
    command = "";

  /* The query prefix */
  strcpy (buf, "qRcmd,");
  p = strchr (buf, '\0');

  if ((strlen (buf) + strlen (command) * 2 + 8/*misc*/) > (rs->remote_packet_size))
    error ("\"monitor\" command ``%s'' is too long\n", command);

  /* Encode the actual command */
  bin2hex (command, p, 0);

  if (putpkt (buf) < 0)
    error ("Communication problem with target\n");

  /* get/display the response */
  while (1)
    {
      /* XXX - see also tracepoint.c:remote_get_noisy_reply() */
      buf[0] = '\0';
      getpkt (buf, (rs->remote_packet_size), 0);
      if (buf[0] == '\0')
	error ("Target does not support this command\n");
      if (buf[0] == 'O' && buf[1] != 'K')
	{
	  remote_console_output (buf + 1); /* 'O' message from stub */
	  continue;
	}
      if (strcmp (buf, "OK") == 0)
	break;
      if (strlen (buf) == 3 && buf[0] == 'E'
	  && isdigit (buf[1]) && isdigit (buf[2]))
	{
	  error ("Protocol error with Rcmd");
	}
      for (p = buf; p[0] != '\0' && p[1] != '\0'; p += 2)
	{
	  char c = (fromhex (p[0]) << 4) + fromhex (p[1]);
	  fputc_unfiltered (c, outbuf);
	}
      break;
    }
}