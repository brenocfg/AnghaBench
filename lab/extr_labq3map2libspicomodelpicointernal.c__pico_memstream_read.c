#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ curPos; scalar_t__ buffer; scalar_t__ bufSize; int /*<<< orphan*/  flag; } ;
typedef  TYPE_1__ picoMemStream_t ;

/* Variables and functions */
 int /*<<< orphan*/  PICO_IOEOF ; 
 int /*<<< orphan*/  memcpy (void*,int,int) ; 

int _pico_memstream_read( picoMemStream_t *s, void *buffer, int len ){
	int ret = 1;

	/* sanity checks */
	if ( s == NULL || buffer == NULL ) {
		return 0;
	}

	if ( s->curPos + len > s->buffer + s->bufSize ) {
		s->flag |= PICO_IOEOF;
		len = s->buffer + s->bufSize - s->curPos;
		ret = 0;
	}

	/* read the data */
	memcpy( buffer, s->curPos, len );
	s->curPos += len;
	return ret;
}