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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 size_t fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * memchr (unsigned char*,char,size_t) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
asciifile(FILE *f)
{
	unsigned char buf[BUFSIZ];
	size_t cnt;

	if (f == NULL)
		return (1);

	rewind(f);
	cnt = fread(buf, 1, sizeof(buf), f);
	return (memchr(buf, '\0', cnt) == NULL);
}