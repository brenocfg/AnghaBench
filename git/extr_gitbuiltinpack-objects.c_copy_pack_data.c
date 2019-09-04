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
struct packed_git {int dummy; } ;
struct pack_window {int dummy; } ;
struct hashfile {int dummy; } ;
typedef  long off_t ;

/* Variables and functions */
 int /*<<< orphan*/  hashwrite (struct hashfile*,unsigned char*,unsigned long) ; 
 unsigned char* use_pack (struct packed_git*,struct pack_window**,long,unsigned long*) ; 

__attribute__((used)) static void copy_pack_data(struct hashfile *f,
		struct packed_git *p,
		struct pack_window **w_curs,
		off_t offset,
		off_t len)
{
	unsigned char *in;
	unsigned long avail;

	while (len) {
		in = use_pack(p, w_curs, offset, &avail);
		if (avail > len)
			avail = (unsigned long)len;
		hashwrite(f, in, avail);
		offset += avail;
		len -= avail;
	}
}