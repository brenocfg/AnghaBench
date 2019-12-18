#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ucl_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_ARRAY ; 
 int /*<<< orphan*/  UCL_OBJECT_BINARY ; 
 int /*<<< orphan*/  UCL_STRING_RAW ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int nelt ; 
 int pcg32_random () ; 
 int /*<<< orphan*/  ucl_array_append (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* ucl_object_fromstring_common (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* ucl_object_typed_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ucl_object_t*
ucl_test_string (void)
{
	ucl_object_t *res, *elt;
	int count, i;
	uint32_t cur_len;
	char *str;

	res = ucl_object_typed_new (UCL_ARRAY);
	count = pcg32_random () % nelt;

	for (i = 0; i < count; i ++) {
		while ((cur_len = pcg32_random ()) % 128 == 0);

		str = malloc (cur_len % 128);
		ucl_array_append (res, ucl_object_fromstring_common (str, cur_len % 128,
				UCL_STRING_RAW));
		free (str);

		while ((cur_len = pcg32_random ()) % 512 == 0);
		str = malloc (cur_len % 512);
		ucl_array_append (res, ucl_object_fromstring_common (str, cur_len % 512,
				UCL_STRING_RAW));
		free (str);

		while ((cur_len = pcg32_random ()) % 128 == 0);
		str = malloc (cur_len % 128);
		elt = ucl_object_fromstring_common (str, cur_len % 128,
				UCL_STRING_RAW);
		elt->flags |= UCL_OBJECT_BINARY;
		ucl_array_append (res, elt);
		free (str);

		while ((cur_len = pcg32_random ()) % 512 == 0);
		str = malloc (cur_len % 512);
		elt = ucl_object_fromstring_common (str, cur_len % 512,
				UCL_STRING_RAW);
		elt->flags |= UCL_OBJECT_BINARY;
		ucl_array_append (res, elt);
		free (str);
	}

	/* One large string */
	str = malloc (65537);
	elt = ucl_object_fromstring_common (str, 65537,
			UCL_STRING_RAW);
	elt->flags |= UCL_OBJECT_BINARY;
	ucl_array_append (res, elt);
	free (str);

	return res;
}