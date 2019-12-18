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
struct open_file {scalar_t__ f_fsdata; } ;
struct bz_file {int /*<<< orphan*/  bzf_rawfd; int /*<<< orphan*/  bzf_bzstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_bzDecompressEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct bz_file*) ; 

__attribute__((used)) static int
bzf_close(struct open_file *f)
{
    struct bz_file	*bzf = (struct bz_file *)f->f_fsdata;
    
    BZ2_bzDecompressEnd(&(bzf->bzf_bzstream));
    close(bzf->bzf_rawfd);
    free(bzf);
    return(0);
}