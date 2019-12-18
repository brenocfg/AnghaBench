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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int EOL ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int logchar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  play (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_close () ; 
 int /*<<< orphan*/  remote_open (char*) ; 
 int /*<<< orphan*/  stderr ; 

int
main (int argc, char *argv[])
{
  FILE *fp;
  int ch;

  if (argc < 3)
    {
      fprintf (stderr, "Usage: gdbreplay <logfile> <host:port>\n");
      fflush (stderr);
      exit (1);
    }
  fp = fopen (argv[1], "r");
  if (fp == NULL)
    {
      perror_with_name (argv[1]);
    }
  remote_open (argv[2]);
  while ((ch = logchar (fp)) != EOF)
    {
      switch (ch)
	{
	case 'w':
	  /* data sent from gdb to gdbreplay, accept and match it */
	  expect (fp);
	  break;
	case 'r':
	  /* data sent from gdbreplay to gdb, play it */
	  play (fp);
	  break;
	case 'c':
	  /* Command executed by gdb */
	  while ((ch = logchar (fp)) != EOL);
	  break;
	}
    }
  remote_close ();
  exit (0);
}