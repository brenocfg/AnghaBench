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
typedef  int /*<<< orphan*/  uintmax_t ;
struct inoinfo {size_t i_number; struct inoinfo* i_nexthash; } ;
typedef  size_t ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIT ; 
 size_t dirhash ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct inoinfo** inphead ; 

struct inoinfo *
getinoinfo(ino_t inumber)
{
	struct inoinfo *inp;

	for (inp = inphead[inumber % dirhash]; inp; inp = inp->i_nexthash) {
		if (inp->i_number != inumber)
			continue;
		return (inp);
	}
	errx(EEXIT, "cannot find inode %ju", (uintmax_t)inumber);
	return ((struct inoinfo *)0);
}