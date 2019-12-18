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
struct z_file {int /*<<< orphan*/  zf_rawfd; int /*<<< orphan*/  zf_zstream; } ;
struct open_file {scalar_t__ f_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct z_file*) ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zf_close(struct open_file *f)
{
    struct z_file	*zf = (struct z_file *)f->f_fsdata;
    
    inflateEnd(&(zf->zf_zstream));
    close(zf->zf_rawfd);
    free(zf);
    return(0);
}