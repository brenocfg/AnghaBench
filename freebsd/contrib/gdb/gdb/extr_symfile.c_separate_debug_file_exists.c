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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 unsigned long gnu_debuglink_crc32 (unsigned long,char*,int) ; 
 int open (char const*,int) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static int
separate_debug_file_exists (const char *name, unsigned long crc)
{
  unsigned long file_crc = 0;
  int fd;
  char buffer[8*1024];
  int count;

  fd = open (name, O_RDONLY | O_BINARY);
  if (fd < 0)
    return 0;

  while ((count = read (fd, buffer, sizeof (buffer))) > 0)
    file_crc = gnu_debuglink_crc32 (file_crc, buffer, count);

  close (fd);

  return crc == file_crc;
}