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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_OK ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int /*<<< orphan*/  S_ISFIFO (int /*<<< orphan*/ ) ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ mkfifo (char const*,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
ws_setfifo (const char *pipename)
{
  struct stat fistat;
  const char *f = pipename;

  if (access (f, F_OK) == 0)
    return 0;

  if (mkfifo (f, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)
    FATAL ("Unable to set fifo: %s.", strerror (errno));
  if (stat (f, &fistat) < 0)
    FATAL ("Unable to stat fifo: %s.", strerror (errno));
  if (!S_ISFIFO (fistat.st_mode))
    FATAL ("pipe is not a fifo: %s.", strerror (errno));

  return 0;
}