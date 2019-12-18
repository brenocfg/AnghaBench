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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  decode_address (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getpkt (char*) ; 
 int /*<<< orphan*/  hexify (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ putpkt (char*) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

int
look_up_one_symbol (const char *name, CORE_ADDR *addrp)
{
  char own_buf[266], *p, *q;
  int len;

  /* Send the request.  */
  strcpy (own_buf, "qSymbol:");
  hexify (own_buf + strlen ("qSymbol:"), name, strlen (name));
  if (putpkt (own_buf) < 0)
    return -1;

  /* FIXME:  Eventually add buffer overflow checking (to getpkt?)  */
  len = getpkt (own_buf);
  if (len < 0)
    return -1;

  if (strncmp (own_buf, "qSymbol:", strlen ("qSymbol:")) != 0)
    {
      /* Malformed response.  */
      if (remote_debug)
	{
	  fprintf (stderr, "Malformed response to qSymbol, ignoring.\n");
	  fflush (stderr);
	}

      return -1;
    }

  p = own_buf + strlen ("qSymbol:");
  q = p;
  while (*q && *q != ':')
    q++;

  /* Make sure we found a value for the symbol.  */
  if (p == q || *q == '\0')
    return 0;

  decode_address (addrp, p, q - p);
  return 1;
}