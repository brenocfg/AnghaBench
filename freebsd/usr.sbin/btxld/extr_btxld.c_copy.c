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
typedef  int off_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fname ; 
 size_t readx (int,char*,size_t,int) ; 
 int /*<<< orphan*/  writex (int,char*,size_t) ; 

__attribute__((used)) static void
copy(int fdi, int fdo, size_t nbyte, off_t offset)
{
    char buf[8192];
    size_t n;

    while (nbyte) {
	if ((n = sizeof(buf)) > nbyte)
	    n = nbyte;
	if (readx(fdi, buf, n, offset) != n)
	    errx(2, "%s: Short read", fname);
	writex(fdo, buf, n);
	nbyte -= n;
	offset = -1;
    }
}