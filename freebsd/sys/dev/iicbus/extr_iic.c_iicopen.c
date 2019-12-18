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
struct iic_cdevpriv {int /*<<< orphan*/  sc; int /*<<< orphan*/  lock; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IIC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int devfs_set_cdevpriv (struct iic_cdevpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct iic_cdevpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicdtor ; 
 struct iic_cdevpriv* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
iicopen(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct iic_cdevpriv *priv;
	int error;

	priv = malloc(sizeof(*priv), M_IIC, M_WAITOK | M_ZERO);

	sx_init(&priv->lock, "iic");
	priv->sc = dev->si_drv1;

	error = devfs_set_cdevpriv(priv, iicdtor); 
	if (error != 0)
		free(priv, M_IIC);

	return (error);
}