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
 unsigned char* bp ; 
 unsigned char* buf ; 
 int /*<<< orphan*/  fputc (unsigned char,int /*<<< orphan*/ *) ; 

void
dump_buffer(FILE *f, size_t m)
{
	unsigned char *s;

	for (s = bp; s-buf > (long)m;)
		fputc(*--s, f);
}