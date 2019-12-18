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
struct uio {int uio_resid; } ;
struct sbuf {int dummy; } ;
struct ledsc {int dummy; } ;
struct cdev {struct ledsc* si_drv1; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_mtx ; 
 int led_parse (char*,struct sbuf**,int*) ; 
 int led_state (struct ledsc*,struct sbuf**,int) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int uiomove (char*,size_t,struct uio*) ; 

__attribute__((used)) static int
led_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct ledsc	*sc;
	char *s;
	struct sbuf *sb = NULL;
	int error, state = 0;

	if (uio->uio_resid > 512)
		return (EINVAL);
	s = malloc(uio->uio_resid + 1, M_DEVBUF, M_WAITOK);
	s[uio->uio_resid] = '\0';
	error = uiomove(s, uio->uio_resid, uio);
	if (error) {
		free(s, M_DEVBUF);
		return (error);
	}
	error = led_parse(s, &sb, &state);
	free(s, M_DEVBUF);
	if (error)
		return (error);
	mtx_lock(&led_mtx);
	sc = dev->si_drv1;
	if (sc != NULL)
		error = led_state(sc, &sb, state);
	mtx_unlock(&led_mtx);
	if (sb != NULL)
		sbuf_delete(sb);
	return (error);
}