#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_7__ {int need_dict_reset; int /*<<< orphan*/  sequence; } ;
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_5__ {int size; int size_max; int end; int allocated; int /*<<< orphan*/ * buf; int /*<<< orphan*/  mode; } ;
struct xz_dec_lzma2 {TYPE_4__ temp; TYPE_3__ lzma2; TYPE_2__ lzma; TYPE_1__ dict; } ;
typedef  enum xz_ret { ____Placeholder_xz_ret } xz_ret ;

/* Variables and functions */
 scalar_t__ DEC_IS_DYNALLOC (int /*<<< orphan*/ ) ; 
 scalar_t__ DEC_IS_MULTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_CONTROL ; 
 int XZ_MEMLIMIT_ERROR ; 
 int XZ_MEM_ERROR ; 
 int XZ_OK ; 
 int XZ_OPTIONS_ERROR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 

enum xz_ret xz_dec_lzma2_reset(struct xz_dec_lzma2 *s, uint8_t props)
{
	/* This limits dictionary size to 3 GiB to keep parsing simpler. */
	if (props > 39)
		return XZ_OPTIONS_ERROR;

	s->dict.size = 2 + (props & 1);
	s->dict.size <<= (props >> 1) + 11;

	if (DEC_IS_MULTI(s->dict.mode)) {
		if (s->dict.size > s->dict.size_max)
			return XZ_MEMLIMIT_ERROR;

		s->dict.end = s->dict.size;

		if (DEC_IS_DYNALLOC(s->dict.mode)) {
			if (s->dict.allocated < s->dict.size) {
				free(s->dict.buf);
				s->dict.buf = malloc(s->dict.size);
				if (s->dict.buf == NULL) {
					s->dict.allocated = 0;
					return XZ_MEM_ERROR;
				}
			}
		}
	}

	s->lzma.len = 0;

	s->lzma2.sequence = SEQ_CONTROL;
	s->lzma2.need_dict_reset = 1;

	s->temp.size = 0;

	return XZ_OK;
}