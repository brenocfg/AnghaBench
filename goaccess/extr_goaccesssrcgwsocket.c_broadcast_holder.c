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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pack_uint32 (char*,int) ; 
 int /*<<< orphan*/  write_holder (int,char const*,int) ; 

int
broadcast_holder (int fd, const char *buf, int len)
{
  char *p = NULL, *ptr = NULL;

  p = calloc (sizeof (uint32_t) * 3, sizeof (char));

  ptr = p;
  ptr += pack_uint32 (ptr, 0);
  ptr += pack_uint32 (ptr, 0x01);
  ptr += pack_uint32 (ptr, len);

  write_holder (fd, p, sizeof (uint32_t) * 3);
  write_holder (fd, buf, len);
  free (p);

  return 0;
}