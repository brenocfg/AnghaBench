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
struct fwimage_trailer {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (struct fwimage_trailer*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trailer_update_crc (struct fwimage_trailer*,struct fwimage_trailer*,int) ; 

__attribute__((used)) static void
append_trailer(FILE *out, struct fwimage_trailer *tr)
{
	tr->size = cpu_to_be32(tr->size);
	fwrite(tr, sizeof(*tr), 1, out);
	trailer_update_crc(tr, tr, sizeof(*tr));
}