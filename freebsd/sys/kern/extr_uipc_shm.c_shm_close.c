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
struct shmfd {int dummy; } ;
struct file {struct shmfd* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  shm_drop (struct shmfd*) ; 

__attribute__((used)) static int
shm_close(struct file *fp, struct thread *td)
{
	struct shmfd *shmfd;

	shmfd = fp->f_data;
	fp->f_data = NULL;
	shm_drop(shmfd);

	return (0);
}