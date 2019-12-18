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
struct open_file {struct bz_file* f_fsdata; } ;
struct bz_file {int /*<<< orphan*/  bzf_bzstream; int /*<<< orphan*/  bzf_rawfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_bzDecompressEnd (int /*<<< orphan*/ *) ; 
 scalar_t__ BZ2_bzDecompressInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ BZ_OK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  bzero (struct bz_file*,int) ; 
 int /*<<< orphan*/  free (struct bz_file*) ; 
 int lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bz_file* malloc (int) ; 

__attribute__((used)) static int
bzf_rewind(struct open_file *f)
{
    struct bz_file	*bzf = (struct bz_file *)f->f_fsdata;
    struct bz_file	*bzf_tmp;

    /*
     * Since bzip2 does not have an equivalent inflateReset function a crude
     * one needs to be provided.  The functions all called in such a way that
     * at any time an error occurs a roll back can be done (effectively making
     * this rewind 'atomic', either the reset occurs successfully or not at all,
     * with no 'undefined' state happening).
     */

    /* Allocate a bz_file structure, populate it */
    bzf_tmp = malloc(sizeof(struct bz_file));
    if (bzf_tmp == NULL)
	return(-1);
    bzero(bzf_tmp, sizeof(struct bz_file));
    bzf_tmp->bzf_rawfd = bzf->bzf_rawfd;

    /* Initialise the inflation engine */
    if (BZ2_bzDecompressInit(&(bzf_tmp->bzf_bzstream), 0, 1) != BZ_OK) {
	free(bzf_tmp);
	return(-1);
    }

    /* Seek back to the beginning of the file */
    if (lseek(bzf->bzf_rawfd, 0, SEEK_SET) == -1) {
	BZ2_bzDecompressEnd(&(bzf_tmp->bzf_bzstream));
	free(bzf_tmp);
	return(-1);
    }

    /* Free old bz_file data */
    BZ2_bzDecompressEnd(&(bzf->bzf_bzstream));
    free(bzf);

    /* Use the new bz_file data */
    f->f_fsdata = bzf_tmp;

    return(0);
}