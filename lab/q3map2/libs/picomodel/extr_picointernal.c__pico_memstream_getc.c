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
 scalar_t__ _pico_memstream_read (int /*<<< orphan*/ *,int*,int) ; 

int _pico_memstream_getc( picoMemStream_t *s ){
	int c = 0;

	/* sanity check */
	if ( s == NULL ) {
		return -1;
	}

	/* read the character */
	if ( _pico_memstream_read( s, &c, 1 ) == 0 ) {
		return -1;
	}

	return c;
}