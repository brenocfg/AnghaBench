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
typedef  int /*<<< orphan*/  splash_decoder_t ;

/* Variables and functions */
 int DECODER_ARRAY_DELTA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** decoder_set ; 
 int decoders ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * splash_adp ; 
 int /*<<< orphan*/ * splash_decoder ; 
 int /*<<< orphan*/  splash_new (int /*<<< orphan*/ *) ; 
 int splash_term (int /*<<< orphan*/ *) ; 
 int splash_test (int /*<<< orphan*/ *) ; 

int
splash_register(splash_decoder_t *decoder)
{
	splash_decoder_t **p;
	int error;
	int i;

	if (splash_adp != NULL) {
		/*
		 * If the video card has already been initialized, test
		 * this decoder immediately.
		 */
		error = splash_test(decoder);
		if (error == 0) {
			/* replace the current decoder with new one */
			if (splash_decoder != NULL)
				error = splash_term(splash_adp);
			if (error == 0)
				splash_new(decoder);
		}
		return error;
	} else {
		/* register the decoder for later use */
		for (i = 0; i < decoders; ++i) {
			if (decoder_set[i] == NULL)
				break;
		}
		if ((i >= decoders) && (decoders % DECODER_ARRAY_DELTA) == 0) {
			p = malloc(sizeof(*p)*(decoders + DECODER_ARRAY_DELTA),
			   	M_DEVBUF, M_NOWAIT);
			if (p == NULL)
				return ENOMEM;
			if (decoder_set != NULL) {
				bcopy(decoder_set, p, sizeof(*p)*decoders);
				free(decoder_set, M_DEVBUF);
			}
			decoder_set = p;
			i = decoders++;
		}
		decoder_set[i] = decoder;
	}

	return 0;
}