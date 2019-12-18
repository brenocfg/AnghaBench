#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int EOF ; 
 size_t read (int /*<<< orphan*/ ,char*,int) ; 

int
getc(FILE *stream)
{
	char	ch;
	size_t	r;

	if (stream == NULL)
		return EOF;
	r = read(stream->fd, &ch, 1);
	if (r == 1)
		return ch;
	return EOF;
}