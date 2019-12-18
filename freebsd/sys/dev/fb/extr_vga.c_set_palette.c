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
 int copyin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vga_load_palette2 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
set_palette(video_adapter_t *adp, int base, int count,
	    u_char *red, u_char *green, u_char *blue, u_char *trans)
{
    u_char *r;
    u_char *g;
    u_char *b;
    int err;

    if (count < 0 || base < 0 || count > 256 || base > 256 ||
	base + count > 256)
	return EINVAL;

    r = malloc(count*3, M_DEVBUF, M_WAITOK);
    g = r + count;
    b = g + count;
    err = copyin(red, r, count);
    if (!err)
        err = copyin(green, g, count);
    if (!err)
        err = copyin(blue, b, count);
    if (!err)
        err = vga_load_palette2(adp, base, count, r, g, b);
    free(r, M_DEVBUF);

    return (err ? ENODEV : 0);
}