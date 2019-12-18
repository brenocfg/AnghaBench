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
struct fd_info {int dupfd; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 struct fd_info* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct fd_info*) ; 
 int /*<<< orphan*/  idm ; 
 int idm_set (int /*<<< orphan*/ *,int,struct fd_info*) ; 
 int /*<<< orphan*/  mut ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ real ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static int fd_open(void)
{
	struct fd_info *fdi;
	int ret, index;

	fdi = calloc(1, sizeof(*fdi));
	if (!fdi)
		return ERR(ENOMEM);

	index = open("/dev/null", O_RDONLY);
	if (index < 0) {
		ret = index;
		goto err1;
	}

	fdi->dupfd = -1;
	atomic_store(&fdi->refcnt, 1);
	pthread_mutex_lock(&mut);
	ret = idm_set(&idm, index, fdi);
	pthread_mutex_unlock(&mut);
	if (ret < 0)
		goto err2;

	return index;

err2:
	real.close(index);
err1:
	free(fdi);
	return ret;
}