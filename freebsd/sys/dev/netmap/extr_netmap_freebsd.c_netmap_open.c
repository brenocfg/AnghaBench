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
struct netmap_priv_d {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NMG_LOCK () ; 
 int /*<<< orphan*/  NMG_UNLOCK () ; 
 int devfs_set_cdevpriv (struct netmap_priv_d*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netmap_dtor ; 
 int /*<<< orphan*/  netmap_priv_delete (struct netmap_priv_d*) ; 
 struct netmap_priv_d* netmap_priv_new () ; 

__attribute__((used)) static int
netmap_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	struct netmap_priv_d *priv;
	int error;

	(void)dev;
	(void)oflags;
	(void)devtype;
	(void)td;

	NMG_LOCK();
	priv = netmap_priv_new();
	if (priv == NULL) {
		error = ENOMEM;
		goto out;
	}
	error = devfs_set_cdevpriv(priv, netmap_dtor);
	if (error) {
		netmap_priv_delete(priv);
	}
out:
	NMG_UNLOCK();
	return error;
}