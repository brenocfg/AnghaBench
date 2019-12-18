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
struct shmfd {int shm_seals; } ;
struct file {struct shmfd* f_data; } ;

/* Variables and functions */

__attribute__((used)) static int
shm_get_seals(struct file *fp, int *seals)
{
	struct shmfd *shmfd;

	shmfd = fp->f_data;
	*seals = shmfd->shm_seals;
	return (0);
}