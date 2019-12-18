#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  uint8_t ;
struct ses_iterator {int dummy; } ;
struct enc_fsm_state {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  enc_daemon_cache; } ;
typedef  TYPE_1__ enc_softc_t ;
typedef  int /*<<< orphan*/  enc_element_t ;
typedef  int /*<<< orphan*/  enc_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ses_iter_init (TYPE_1__*,int /*<<< orphan*/ *,struct ses_iterator*) ; 
 int /*<<< orphan*/ * ses_iter_next (struct ses_iterator*) ; 
 int /*<<< orphan*/  ses_print_addl_data (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ses_set_physpath (TYPE_1__*,int /*<<< orphan*/ *,struct ses_iterator*) ; 

__attribute__((used)) static int
ses_publish_physpaths(enc_softc_t *enc, struct enc_fsm_state *state,
    union ccb *ccb, uint8_t **bufp, int error, int xfer_len)
{
	struct ses_iterator iter;
	enc_cache_t *enc_cache;
	enc_element_t *element;

	enc_cache = &enc->enc_daemon_cache;

	ses_iter_init(enc, enc_cache, &iter);
	while ((element = ses_iter_next(&iter)) != NULL) {
		/*
		 * ses_set_physpath() returns success if we changed
		 * the physpath of any element.  This allows us to
		 * only announce devices once regardless of how
		 * many times we process additional element status.
		 */
		if (ses_set_physpath(enc, element, &iter) == 0)
			ses_print_addl_data(enc, element);
	}

	return (0);
}