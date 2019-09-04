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
struct xz_dec {int /*<<< orphan*/  lzma2; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct xz_dec*) ; 
 int /*<<< orphan*/  xz_dec_lzma2_end (int /*<<< orphan*/ ) ; 

void xz_dec_end(struct xz_dec *s)
{
	if (s != NULL) {
		xz_dec_lzma2_end(s->lzma2);
		free(s);
	}
}