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
typedef  int u_long ;
typedef  int u_int32_t ;
struct thread {int dummy; } ;
struct file {int dummy; } ;
struct fcrypt {int /*<<< orphan*/  sesn; int /*<<< orphan*/  csessions; } ;
struct crypt_find_op {int dummy; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  CRIOASYMFEAT 130 
#define  CRIOFINDDEV 129 
#define  CRIOGET 128 
 int /*<<< orphan*/  DTYPE_CRYPTO ; 
 int EINVAL ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  M_XDATA ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int crypto_getfeat (int*) ; 
 int cryptodev_find (struct crypt_find_op*) ; 
 int /*<<< orphan*/  cryptofops ; 
 int falloc (struct thread*,struct file**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct fcrypt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct fcrypt*,int /*<<< orphan*/ ) ; 
 struct fcrypt* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cryptoioctl(struct cdev *dev, u_long cmd, caddr_t data, int flag, struct thread *td)
{
	struct file *f;
	struct fcrypt *fcr;
	int fd, error;

	switch (cmd) {
	case CRIOGET:
		fcr = malloc(sizeof(struct fcrypt), M_XDATA, M_WAITOK);
		TAILQ_INIT(&fcr->csessions);
		fcr->sesn = 0;

		error = falloc(td, &f, &fd, 0);

		if (error) {
			free(fcr, M_XDATA);
			return (error);
		}
		/* falloc automatically provides an extra reference to 'f'. */
		finit(f, FREAD | FWRITE, DTYPE_CRYPTO, fcr, &cryptofops);
		*(u_int32_t *)data = fd;
		fdrop(f, td);
		break;
	case CRIOFINDDEV:
		error = cryptodev_find((struct crypt_find_op *)data);
		break;
	case CRIOASYMFEAT:
		error = crypto_getfeat((int *)data);
		break;
	default:
		error = EINVAL;
		break;
	}
	return (error);
}