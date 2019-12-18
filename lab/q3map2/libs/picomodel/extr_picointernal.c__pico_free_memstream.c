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
typedef  int /*<<< orphan*/  picoMemStream_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_free (int /*<<< orphan*/ *) ; 

void _pico_free_memstream( picoMemStream_t *s ){
	/* sanity check */
	if ( s == NULL ) {
		return;
	}

	/* free the stream */
	_pico_free( s );
}