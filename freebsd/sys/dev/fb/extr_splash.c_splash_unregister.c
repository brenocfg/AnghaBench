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
 int /*<<< orphan*/  splash_adp ; 
 int /*<<< orphan*/ * splash_decoder ; 
 int splash_term (int /*<<< orphan*/ ) ; 

int
splash_unregister(splash_decoder_t *decoder)
{
	int error;

	if (splash_decoder == decoder) {
		if ((error = splash_term(splash_adp)) != 0)
			return error;
	}
	return 0;
}