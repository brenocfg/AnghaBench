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

/* Variables and functions */
 scalar_t__ FLEN_ERROR ; 
 char* _pico_alloc (int) ; 
 scalar_t__ flen ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,int) ; 
 int strlen (char*) ; 

char *sgetS0( unsigned char **bp ){
	char *s;
	unsigned char *buf = *bp;
	int len;

	if ( flen == FLEN_ERROR ) {
		return NULL;
	}

	len = strlen( (char *) buf ) + 1;
	if ( len == 1 ) {
		flen += 2;
		*bp += 2;
		return NULL;
	}
	len += len & 1;
	s = _pico_alloc( len );
	if ( !s ) {
		flen = FLEN_ERROR;
		return NULL;
	}

	memcpy( s, buf, len );
	flen += len;
	*bp += len;
	return s;
}