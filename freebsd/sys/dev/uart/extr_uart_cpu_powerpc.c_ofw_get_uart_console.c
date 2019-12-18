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
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENXIO ; 
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char const*,char*,int) ; 

__attribute__((used)) static int
ofw_get_uart_console(phandle_t opts, phandle_t *result, const char *inputdev,
    const char *outputdev)
{
	char buf[64];
	phandle_t input;

	if (OF_getprop(opts, inputdev, buf, sizeof(buf)) == -1)
		return (ENXIO);
	input = OF_finddevice(buf);
	if (input == -1)
		return (ENXIO);

	if (outputdev != NULL) {
		if (OF_getprop(opts, outputdev, buf, sizeof(buf)) == -1)
			return (ENXIO);
		if (OF_finddevice(buf) != input)
			return (ENXIO);
	}

	*result = input;
	return (0);
}