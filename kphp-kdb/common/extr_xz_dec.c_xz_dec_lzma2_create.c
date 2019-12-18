#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int mode; scalar_t__ allocated; int /*<<< orphan*/ * buf; int /*<<< orphan*/  size_max; } ;
struct xz_dec_lzma2 {TYPE_1__ dict; } ;
typedef  enum xz_mode { ____Placeholder_xz_mode } xz_mode ;

/* Variables and functions */
 scalar_t__ DEC_IS_DYNALLOC (int) ; 
 scalar_t__ DEC_IS_PREALLOC (int) ; 
 struct xz_dec_lzma2* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct xz_dec_lzma2*) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

struct xz_dec_lzma2 *xz_dec_lzma2_create(enum xz_mode mode,
						   uint32_t dict_max)
{
	struct xz_dec_lzma2 *s = calloc(sizeof(*s), 1);
	if (s == NULL)
		return NULL;

	s->dict.mode = mode;
	s->dict.size_max = dict_max;

	if (DEC_IS_PREALLOC(mode)) {
		s->dict.buf = malloc(dict_max);
		if (s->dict.buf == NULL) {
			free(s);
			return NULL;
		}
	} else if (DEC_IS_DYNALLOC(mode)) {
		s->dict.buf = NULL;
		s->dict.allocated = 0;
	}

	return s;
}