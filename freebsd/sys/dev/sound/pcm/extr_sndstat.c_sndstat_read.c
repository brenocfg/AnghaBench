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
struct uio {int uio_resid; } ;
struct sndstat_file {scalar_t__ out_offset; scalar_t__ in_offset; int /*<<< orphan*/  sbuf; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SNDSTAT_LOCK () ; 
 int /*<<< orphan*/  SNDSTAT_UNLOCK () ; 
 int devfs_get_cdevpriv (void**) ; 
 int sbuf_data (int /*<<< orphan*/ *) ; 
 int sbuf_len (int /*<<< orphan*/ *) ; 
 int sndstat_prepare (struct sndstat_file*) ; 
 int uiomove (int,int,struct uio*) ; 

__attribute__((used)) static int
sndstat_read(struct cdev *i_dev, struct uio *buf, int flag)
{
	struct sndstat_file *pf;
	int err;
	int len;

	err = devfs_get_cdevpriv((void **)&pf);
	if (err != 0)
		return (err);

	/* skip zero-length reads */
	if (buf->uio_resid == 0)
		return (0);

	SNDSTAT_LOCK();
	if (pf->out_offset != 0) {
		/* don't allow both reading and writing */
		err = EINVAL;
		goto done;
	} else if (pf->in_offset == 0) {
		err = sndstat_prepare(pf);
		if (err <= 0) {
			err = ENOMEM;
			goto done;
		}
	}
	len = sbuf_len(&pf->sbuf) - pf->in_offset;
	if (len > buf->uio_resid)
		len = buf->uio_resid;
	if (len > 0)
		err = uiomove(sbuf_data(&pf->sbuf) + pf->in_offset, len, buf);
	pf->in_offset += len;
done:
	SNDSTAT_UNLOCK();
	return (err);
}