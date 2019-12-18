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
struct bhnd_nvram_io {int dummy; } ;
struct bcm_nvram_iocfe {size_t offset; size_t size; int /*<<< orphan*/  fd; } ;
typedef  size_t int64_t ;

/* Variables and functions */
 int ENXIO ; 
 size_t INT64_MAX ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  IOCFE_LOG (struct bcm_nvram_iocfe*,char*,int,...) ; 
 int cfe_readblk (int /*<<< orphan*/ ,size_t,void*,int) ; 
 int ummin (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
bhnd_nvram_iocfe_read(struct bhnd_nvram_io *io, size_t offset, void *buffer,
    size_t nbytes)
{
	struct bcm_nvram_iocfe	*iocfe;
	size_t			 remain;
	int64_t			 cfe_offset;
	int			 nr, nreq;

	iocfe = (struct bcm_nvram_iocfe *)io;

	/* Determine (and validate) the base CFE offset */
#if (SIZE_MAX > INT64_MAX)
	if (iocfe->offset > INT64_MAX || offset > INT64_MAX)
		return (ENXIO);
#endif

	if (INT64_MAX - offset < iocfe->offset)
		return (ENXIO);

	cfe_offset = iocfe->offset + offset;

	/* Verify that cfe_offset + nbytes is representable */
	if (INT64_MAX - cfe_offset < nbytes)
		return (ENXIO);

	/* Perform the read */
	for (remain = nbytes; remain > 0;) {
		void	*p;
		size_t	 nread;
		int64_t	 cfe_noff;

		nread = (nbytes - remain);
		cfe_noff = cfe_offset + nread;
		p = ((uint8_t *)buffer + nread);
		nreq = ummin(INT_MAX, remain);
	
		nr = cfe_readblk(iocfe->fd, cfe_noff, p, nreq);
		if (nr < 0) {
			IOCFE_LOG(iocfe, "cfe_readblk() failed: %d\n", nr);
			return (ENXIO);
		}

		/* Check for unexpected short read */
		if (nr == 0 && remain > 0) {
			/* If the request fits entirely within the CFE
			 * device range, we shouldn't hit EOF */
			if (remain < iocfe->size &&
			    iocfe->size - remain > offset)
			{
				IOCFE_LOG(iocfe, "cfe_readblk() returned "
				    "unexpected short read (%d/%d)\n", nr,
				    nreq);
				return (ENXIO);
			}
		}

		if (nr == 0)
			break;

		remain -= nr;
	}

	/* Check for short read */
	if (remain > 0)
		return (ENXIO);

	return (0);
}