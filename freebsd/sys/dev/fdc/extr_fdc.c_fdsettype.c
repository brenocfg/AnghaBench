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
struct fd_type {int size; int sectrac; int heads; int tracks; int secsize; } ;
struct fd_data {int sectorsize; struct fd_type* ft; } ;

/* Variables and functions */

__attribute__((used)) static void
fdsettype(struct fd_data *fd, struct fd_type *ft)
{
	fd->ft = ft;
	ft->size = ft->sectrac * ft->heads * ft->tracks;
	fd->sectorsize = 128 << fd->ft->secsize;
}