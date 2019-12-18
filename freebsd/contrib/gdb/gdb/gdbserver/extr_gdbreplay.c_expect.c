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
 int EOL ; 
 int logchar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  remote_desc ; 
 int /*<<< orphan*/  sync_error (int /*<<< orphan*/ *,char*,int,unsigned char) ; 

__attribute__((used)) static void
expect (FILE *fp)
{
  int fromlog;
  unsigned char fromgdb;

  if ((fromlog = logchar (fp)) != ' ')
    {
      sync_error (fp, "Sync error during gdb read of leading blank", ' ',
		  fromlog);
    }
  do
    {
      fromlog = logchar (fp);
      if (fromlog == EOL)
	{
	  break;
	}
      read (remote_desc, &fromgdb, 1);
    }
  while (fromlog == fromgdb);
  if (fromlog != EOL)
    {
      sync_error (fp, "Sync error during read of gdb packet", fromlog,
		  fromgdb);
    }
}