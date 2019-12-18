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
struct udf_dirstream {scalar_t__ offset; size_t off; scalar_t__ fsize; int error; scalar_t__ size; int fid_fragment; scalar_t__ this_off; int /*<<< orphan*/ * buf; struct fileid_desc* data; TYPE_1__* udfmp; int /*<<< orphan*/ * bp; int /*<<< orphan*/  node; } ;
struct fileid_desc {scalar_t__ l_fi; int /*<<< orphan*/  l_iu; } ;
struct TYPE_2__ {int bsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  M_UDFFID ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ UDF_FID_SIZE ; 
 int /*<<< orphan*/  bcopy (struct fileid_desc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int udf_readatoffset (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ **,struct fileid_desc**) ; 

__attribute__((used)) static struct fileid_desc *
udf_getfid(struct udf_dirstream *ds)
{
	struct fileid_desc *fid;
	int error, frag_size = 0, total_fid_size;

	/* End of directory? */
	if (ds->offset + ds->off >= ds->fsize) {
		ds->error = 0;
		return (NULL);
	}

	/* Grab the first extent of the directory */
	if (ds->off == 0) {
		ds->size = 0;
		error = udf_readatoffset(ds->node, &ds->size, ds->offset,
		    &ds->bp, &ds->data);
		if (error) {
			ds->error = error;
			if (ds->bp != NULL)
				brelse(ds->bp);
			return (NULL);
		}
	}

	/*
	 * Clean up from a previous fragmented FID.
	 * XXX Is this the right place for this?
	 */
	if (ds->fid_fragment && ds->buf != NULL) {
		ds->fid_fragment = 0;
		free(ds->buf, M_UDFFID);
	}

	fid = (struct fileid_desc*)&ds->data[ds->off];

	/*
	 * Check to see if the fid is fragmented. The first test
	 * ensures that we don't wander off the end of the buffer
	 * looking for the l_iu and l_fi fields.
	 */
	if (ds->off + UDF_FID_SIZE > ds->size ||
	    ds->off + le16toh(fid->l_iu) + fid->l_fi + UDF_FID_SIZE > ds->size){

		/* Copy what we have of the fid into a buffer */
		frag_size = ds->size - ds->off;
		if (frag_size >= ds->udfmp->bsize) {
			printf("udf: invalid FID fragment\n");
			ds->error = EINVAL;
			return (NULL);
		}

		/*
		 * File ID descriptors can only be at most one
		 * logical sector in size.
		 */
		ds->buf = malloc(ds->udfmp->bsize, M_UDFFID,
		     M_WAITOK | M_ZERO);
		bcopy(fid, ds->buf, frag_size);

		/* Reduce all of the casting magic */
		fid = (struct fileid_desc*)ds->buf;

		if (ds->bp != NULL)
			brelse(ds->bp);

		/* Fetch the next allocation */
		ds->offset += ds->size;
		ds->size = 0;
		error = udf_readatoffset(ds->node, &ds->size, ds->offset,
		    &ds->bp, &ds->data);
		if (error) {
			ds->error = error;
			return (NULL);
		}

		/*
		 * If the fragment was so small that we didn't get
		 * the l_iu and l_fi fields, copy those in.
		 */
		if (frag_size < UDF_FID_SIZE)
			bcopy(ds->data, &ds->buf[frag_size],
			    UDF_FID_SIZE - frag_size);

		/*
		 * Now that we have enough of the fid to work with,
		 * copy in the rest of the fid from the new
		 * allocation.
		 */
		total_fid_size = UDF_FID_SIZE + le16toh(fid->l_iu) + fid->l_fi;
		if (total_fid_size > ds->udfmp->bsize) {
			printf("udf: invalid FID\n");
			ds->error = EIO;
			return (NULL);
		}
		bcopy(ds->data, &ds->buf[frag_size],
		    total_fid_size - frag_size);

		ds->fid_fragment = 1;
	} else {
		total_fid_size = le16toh(fid->l_iu) + fid->l_fi + UDF_FID_SIZE;
	}

	/*
	 * Update the offset. Align on a 4 byte boundary because the
	 * UDF spec says so.
	 */
	ds->this_off = ds->offset + ds->off;
	if (!ds->fid_fragment) {
		ds->off += (total_fid_size + 3) & ~0x03;
	} else {
		ds->off = (total_fid_size - frag_size + 3) & ~0x03;
	}

	return (fid);
}