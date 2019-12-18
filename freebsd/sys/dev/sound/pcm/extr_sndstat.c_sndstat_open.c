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
struct thread {int dummy; } ;
struct sndstat_file {int /*<<< orphan*/  sbuf; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SBUF_AUTOEXTEND ; 
 int /*<<< orphan*/  SNDSTAT_LOCK () ; 
 int /*<<< orphan*/  SNDSTAT_UNLOCK () ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct sndstat_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_set_cdevpriv (struct sndstat_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct sndstat_file*,int /*<<< orphan*/ ) ; 
 struct sndstat_file* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndstat_close ; 
 int /*<<< orphan*/  sndstat_filelist ; 

__attribute__((used)) static int
sndstat_open(struct cdev *i_dev, int flags, int mode, struct thread *td)
{
	struct sndstat_file *pf;

	pf = malloc(sizeof(*pf), M_DEVBUF, M_WAITOK | M_ZERO);

	SNDSTAT_LOCK();
	if (sbuf_new(&pf->sbuf, NULL, 4096, SBUF_AUTOEXTEND) == NULL) {
	  	SNDSTAT_UNLOCK();
		free(pf, M_DEVBUF);
		return (ENOMEM);
	}
	TAILQ_INSERT_TAIL(&sndstat_filelist, pf, entry);
	SNDSTAT_UNLOCK();

	devfs_set_cdevpriv(pf, &sndstat_close);

	return (0);
}