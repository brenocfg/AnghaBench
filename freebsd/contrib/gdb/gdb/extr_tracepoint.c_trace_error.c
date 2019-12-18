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
 int /*<<< orphan*/  error (char*,...) ; 
 char* strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
trace_error (char *buf)
{
  if (*buf++ != 'E')
    return;			/* not an error msg */
  switch (*buf)
    {
    case '1':			/* malformed packet error */
      if (*++buf == '0')	/*   general case: */
	error ("tracepoint.c: error in outgoing packet.");
      else
	error ("tracepoint.c: error in outgoing packet at field #%ld.",
	       strtol (buf, NULL, 16));
    case '2':
      error ("trace API error 0x%s.", ++buf);
    default:
      error ("Target returns error code '%s'.", buf);
    }
}