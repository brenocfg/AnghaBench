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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  temp ;
struct uio {int uio_resid; } ;
struct sndstat_file {scalar_t__ in_offset; scalar_t__ out_offset; int /*<<< orphan*/  sbuf; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SNDSTAT_LOCK () ; 
 int /*<<< orphan*/  SNDSTAT_UNLOCK () ; 
 int devfs_get_cdevpriv (void**) ; 
 scalar_t__ sbuf_bcat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sbuf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_finish (int /*<<< orphan*/ *) ; 
 scalar_t__ sbuf_len (int /*<<< orphan*/ *) ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

__attribute__((used)) static int
sndstat_write(struct cdev *i_dev, struct uio *buf, int flag)
{
	struct sndstat_file *pf;
	uint8_t temp[64];
	int err;
	int len;

	err = devfs_get_cdevpriv((void **)&pf);
	if (err != 0)
		return (err);

	/* skip zero-length writes */
	if (buf->uio_resid == 0)
		return (0);

	/* don't allow writing more than 64Kbytes */
	if (buf->uio_resid > 65536)
		return (ENOMEM);

	SNDSTAT_LOCK();
	if (pf->in_offset != 0) {
		/* don't allow both reading and writing */
		err = EINVAL;
	} else {
		/* only remember the last write - allows for updates */
		sbuf_clear(&pf->sbuf);
		while (1) {
			len = sizeof(temp);
			if (len > buf->uio_resid)
				len = buf->uio_resid;
			if (len > 0) {
				err = uiomove(temp, len, buf);
				if (err)
					break;
			} else {
				break;
			}
			if (sbuf_bcat(&pf->sbuf, temp, len) < 0) {
				err = ENOMEM;
				break;
			}
		}
		sbuf_finish(&pf->sbuf);
		if (err == 0)
			pf->out_offset = sbuf_len(&pf->sbuf);
		else
			pf->out_offset = 0;
	}
	SNDSTAT_UNLOCK();
	return (err);
}