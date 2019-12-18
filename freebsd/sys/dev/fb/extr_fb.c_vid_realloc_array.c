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
struct cdevsw {int dummy; } ;
typedef  struct cdevsw video_switch_t ;
typedef  struct cdevsw video_adapter_t ;

/* Variables and functions */
 scalar_t__ ARRAY_DELTA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct cdevsw** adapter ; 
 int adapters ; 
 int /*<<< orphan*/  bcopy (struct cdevsw**,struct cdevsw**,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  free (struct cdevsw**,int /*<<< orphan*/ ) ; 
 struct cdevsw** malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int rounddown (scalar_t__,scalar_t__) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  vid_malloc ; 
 struct cdevsw** vidcdevsw ; 
 struct cdevsw** vidsw ; 

__attribute__((used)) static int
vid_realloc_array(void)
{
	video_adapter_t **new_adp;
	video_switch_t **new_vidsw;
#ifdef FB_INSTALL_CDEV
	struct cdevsw **new_cdevsw;
#endif
	int newsize;
	int s;

	if (!vid_malloc)
		return ENOMEM;

	s = spltty();
	newsize = rounddown(adapters + ARRAY_DELTA, ARRAY_DELTA);
	new_adp = malloc(sizeof(*new_adp)*newsize, M_DEVBUF, M_WAITOK | M_ZERO);
	new_vidsw = malloc(sizeof(*new_vidsw)*newsize, M_DEVBUF,
	    M_WAITOK | M_ZERO);
#ifdef FB_INSTALL_CDEV
	new_cdevsw = malloc(sizeof(*new_cdevsw)*newsize, M_DEVBUF,
	    M_WAITOK | M_ZERO);
#endif
	bcopy(adapter, new_adp, sizeof(*adapter)*adapters);
	bcopy(vidsw, new_vidsw, sizeof(*vidsw)*adapters);
#ifdef FB_INSTALL_CDEV
	bcopy(vidcdevsw, new_cdevsw, sizeof(*vidcdevsw)*adapters);
#endif
	if (adapters > 1) {
		free(adapter, M_DEVBUF);
		free(vidsw, M_DEVBUF);
#ifdef FB_INSTALL_CDEV
		free(vidcdevsw, M_DEVBUF);
#endif
	}
	adapter = new_adp;
	vidsw = new_vidsw;
#ifdef FB_INSTALL_CDEV
	vidcdevsw = new_cdevsw;
#endif
	adapters = newsize;
	splx(s);

	if (bootverbose)
		printf("fb: new array size %d\n", adapters);

	return 0;
}