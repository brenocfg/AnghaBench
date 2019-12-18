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
typedef  int /*<<< orphan*/  video_adapter_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vga_save_palette2 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_palette(video_adapter_t *adp, int base, int count,
	    u_char *red, u_char *green, u_char *blue, u_char *trans)
{
    u_char *r;
    u_char *g;
    u_char *b;

    if (count < 0 || base < 0 || count > 256 || base > 256 ||
	base + count > 256)
	return EINVAL;

    r = malloc(count*3, M_DEVBUF, M_WAITOK);
    g = r + count;
    b = g + count;
    if (vga_save_palette2(adp, base, count, r, g, b)) {
	free(r, M_DEVBUF);
	return ENODEV;
    }
    copyout(r, red, count);
    copyout(g, green, count);
    copyout(b, blue, count);
    if (trans != NULL) {
	bzero(r, count);
	copyout(r, trans, count);
    }
    free(r, M_DEVBUF);

    return 0;
}