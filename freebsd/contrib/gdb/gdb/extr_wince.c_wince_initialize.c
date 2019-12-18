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
typedef  int /*<<< orphan*/  tmp ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  args ;
typedef  int /*<<< orphan*/  PROCESS_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  CeCreateProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* CeGetLastError () ; 
 int CeRapiInit () ; 
 int /*<<< orphan*/  CeRapiUninit () ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  WINCE_STUB ; 
 int /*<<< orphan*/  accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connection_initialized ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ gethostname (char*,scalar_t__) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ remote_add_host ; 
 int /*<<< orphan*/  s ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  stub_error (char*) ; 
 int /*<<< orphan*/  towide (char*,int /*<<< orphan*/ *) ; 
 char* upload_to_device (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wince_initialize (void)
{
  int tmp;
  char args[256];
  char *hostname;
  struct sockaddr_in sin;
  char *stub_file_name;
  int s0;
  PROCESS_INFORMATION pi;

  if (!connection_initialized)
    switch (CeRapiInit ())
      {
      case 0:
	connection_initialized = 1;
	break;
      default:
	CeRapiUninit ();
	error ("Can't initialize connection to remote device.\n");
	break;
      }

  /* Upload the stub to the handheld device. */
  stub_file_name = upload_to_device ("wince-stub.exe", WINCE_STUB);
  strcpy (args, stub_file_name);

  if (remote_add_host)
    {
      strcat (args, " ");
      hostname = strchr (args, '\0');
      if (gethostname (hostname, sizeof (args) - strlen (args)))
	error ("couldn't get hostname of this system.");
    }

  /* Get a socket. */
  if ((s0 = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    stub_error ("Couldn't connect to host system.");

  /* Allow rapid reuse of the port. */
  tmp = 1;
  (void) setsockopt (s0, SOL_SOCKET, SO_REUSEADDR, (char *) &tmp, sizeof (tmp));


  /* Set up the information for connecting to the host gdb process. */
  memset (&sin, 0, sizeof (sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons (7000);	/* FIXME: This should be configurable */

  if (bind (s0, (struct sockaddr *) &sin, sizeof (sin)))
    error ("couldn't bind socket");

  if (listen (s0, 1))
    error ("Couldn't open socket for listening.\n");

  /* Start up the stub on the remote device. */
  if (!CeCreateProcess (towide (stub_file_name, NULL), towide (args, NULL),
			NULL, NULL, 0, 0, NULL, NULL, NULL, &pi))
    error ("Unable to start remote stub '%s'.  Windows CE error %d.",
	   stub_file_name, CeGetLastError ());

  /* Wait for a connection */

  if ((s = accept (s0, NULL, NULL)) < 0)
    error ("couldn't set up server for connection.");

  close (s0);
}