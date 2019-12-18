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
typedef  int /*<<< orphan*/  uint32_t ;
struct xz_dec {int mode; int /*<<< orphan*/ * lzma2; } ;
typedef  enum xz_mode { ____Placeholder_xz_mode } xz_mode ;

/* Variables and functions */
 struct xz_dec* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct xz_dec*) ; 
 int /*<<< orphan*/ * xz_dec_lzma2_create (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xz_dec_reset (struct xz_dec*) ; 

struct xz_dec *xz_dec_init(enum xz_mode mode, uint32_t dict_max)
{
	struct xz_dec *s = calloc(sizeof(*s), 1);
	if (s == NULL)
		return NULL;

	s->mode = mode;

	s->lzma2 = xz_dec_lzma2_create(mode, dict_max);
	if (s->lzma2 == NULL)
		goto error_lzma2;

	xz_dec_reset(s);
	return s;

error_lzma2:
	free(s);
	return NULL;
}