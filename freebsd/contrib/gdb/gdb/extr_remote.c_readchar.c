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
typedef  enum serial_rc { ____Placeholder_serial_rc } serial_rc ;

/* Variables and functions */
#define  SERIAL_EOF 130 
#define  SERIAL_ERROR 129 
#define  SERIAL_TIMEOUT 128 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  remote_desc ; 
 int serial_readchar (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 

__attribute__((used)) static int
readchar (int timeout)
{
  int ch;

  ch = serial_readchar (remote_desc, timeout);

  if (ch >= 0)
    return (ch & 0x7f);

  switch ((enum serial_rc) ch)
    {
    case SERIAL_EOF:
      target_mourn_inferior ();
      error ("Remote connection closed");
      /* no return */
    case SERIAL_ERROR:
      perror_with_name ("Remote communication error");
      /* no return */
    case SERIAL_TIMEOUT:
      break;
    }
  return ch;
}