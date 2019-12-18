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
typedef  int /*<<< orphan*/  isc_bufferlist_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_BUFFER_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ISC_LIST_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ isc_buffer_usedlength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 

unsigned int
isc_bufferlist_usedcount(isc_bufferlist_t *bl) {
	isc_buffer_t *buffer;
	unsigned int length;

	REQUIRE(bl != NULL);

	length = 0;
	buffer = ISC_LIST_HEAD(*bl);
	while (buffer != NULL) {
		REQUIRE(ISC_BUFFER_VALID(buffer));
		length += isc_buffer_usedlength(buffer);
		buffer = ISC_LIST_NEXT(buffer, link);
	}

	return (length);
}