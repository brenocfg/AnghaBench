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
typedef  int* offsets_t ;
typedef  scalar_t__ bufp ;

/* Variables and functions */
 int debug ; 
 int /*<<< orphan*/  printf (char*,unsigned int,int,unsigned char) ; 

__attribute__((used)) static unsigned char
get_byte(
	 unsigned char *bufp,
	 offsets_t offset,
	 int *fieldindex
	 )
{
  unsigned char val;

  val     = *(bufp + offset[*fieldindex]);
#ifdef LIBDEBUG
  if (debug > 4)
    printf("fetchieee754: getbyte(0x%08x, %d) = 0x%02x\n", (unsigned int)(bufp)+offset[*fieldindex], *fieldindex, val);
#endif
  (*fieldindex)++;
  return val;
}