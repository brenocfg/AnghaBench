#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ses_element_t ;
typedef  int /*<<< orphan*/  ses_cache_t ;
typedef  int /*<<< orphan*/  enc_softc_t ;
struct TYPE_8__ {struct TYPE_8__* elm_private; } ;
typedef  TYPE_1__ enc_element_t ;
struct TYPE_9__ {int nelms; TYPE_1__* elm_map; int /*<<< orphan*/ * private; } ;
typedef  TYPE_2__ enc_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_SCSIENC ; 
 int /*<<< orphan*/  M_WAITOK ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ses_cache_free (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
ses_cache_clone(enc_softc_t *enc, enc_cache_t *src, enc_cache_t *dst)
{
	ses_cache_t   *dst_ses_cache;
	ses_cache_t   *src_ses_cache;
	enc_element_t *src_elm;
	enc_element_t *dst_elm;
	enc_element_t *last_elm;

	ses_cache_free(enc, dst);
	src_ses_cache = src->private;
	dst_ses_cache = dst->private;

	/*
	 * The cloned enclosure cache and ses specific cache are
	 * mostly identical to the source.
	 */
	*dst = *src;
	*dst_ses_cache = *src_ses_cache;

	/*
	 * But the ses cache storage is still independent.  Restore
	 * the pointer that was clobbered by the structure copy above.
	 */
	dst->private = dst_ses_cache;

	/*
	 * The element map is independent even though it starts out
	 * pointing to the same constant page data.
	 */
	dst->elm_map = malloc(dst->nelms * sizeof(enc_element_t),
	    M_SCSIENC, M_WAITOK);
	memcpy(dst->elm_map, src->elm_map, dst->nelms * sizeof(enc_element_t));
	for (dst_elm = dst->elm_map, src_elm = src->elm_map,
	     last_elm = &src->elm_map[src->nelms];
	     src_elm != last_elm; src_elm++, dst_elm++) {

		dst_elm->elm_private = malloc(sizeof(ses_element_t),
		    M_SCSIENC, M_WAITOK);
		memcpy(dst_elm->elm_private, src_elm->elm_private,
		       sizeof(ses_element_t));
	}
}