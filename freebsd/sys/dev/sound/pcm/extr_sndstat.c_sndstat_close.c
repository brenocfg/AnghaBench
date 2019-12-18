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
struct sndstat_file {int /*<<< orphan*/  sbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SNDSTAT_LOCK () ; 
 int /*<<< orphan*/  SNDSTAT_UNLOCK () ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sndstat_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct sndstat_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sndstat_filelist ; 

__attribute__((used)) static void
sndstat_close(void *sndstat_file)
{
	struct sndstat_file *pf = (struct sndstat_file *)sndstat_file;

	SNDSTAT_LOCK();
	sbuf_delete(&pf->sbuf);
	TAILQ_REMOVE(&sndstat_filelist, pf, entry);
	SNDSTAT_UNLOCK();

	free(pf, M_DEVBUF);
}