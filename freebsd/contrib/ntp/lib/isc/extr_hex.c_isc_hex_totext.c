#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_4__ {scalar_t__ length; int* base; } ;
typedef  TYPE_1__ isc_region_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  RETERR (int /*<<< orphan*/ ) ; 
 char* hex ; 
 int /*<<< orphan*/  isc_region_consume (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  str_totext (char const*,int /*<<< orphan*/ *) ; 

isc_result_t
isc_hex_totext(isc_region_t *source, int wordlength,
	       const char *wordbreak, isc_buffer_t *target)
{
	char buf[3];
	unsigned int loops = 0;

	if (wordlength < 2)
		wordlength = 2;

	memset(buf, 0, sizeof(buf));
	while (source->length > 0) {
		buf[0] = hex[(source->base[0] >> 4) & 0xf];
		buf[1] = hex[(source->base[0]) & 0xf];
		RETERR(str_totext(buf, target));
		isc_region_consume(source, 1);

		loops++;
		if (source->length != 0 &&
		    (int)((loops + 1) * 2) >= wordlength)
		{
			loops = 0;
			RETERR(str_totext(wordbreak, target));
		}
	}
	return (ISC_R_SUCCESS);
}