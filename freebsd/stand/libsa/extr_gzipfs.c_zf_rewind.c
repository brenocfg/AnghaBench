#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * next_in; scalar_t__ avail_in; } ;
struct z_file {TYPE_1__ zf_zstream; scalar_t__ zf_endseen; int /*<<< orphan*/  zf_dataoffset; int /*<<< orphan*/  zf_rawfd; } ;
struct open_file {scalar_t__ f_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  inflateReset (TYPE_1__*) ; 
 int lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zf_rewind(struct open_file *f)
{
    struct z_file	*zf = (struct z_file *)f->f_fsdata;

    if (lseek(zf->zf_rawfd, zf->zf_dataoffset, SEEK_SET) == -1)
	return(-1);
    zf->zf_zstream.avail_in = 0;
    zf->zf_zstream.next_in = NULL;
    zf->zf_endseen = 0;
    (void)inflateReset(&zf->zf_zstream);

    return(0);
}