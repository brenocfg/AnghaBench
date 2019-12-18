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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 size_t OF_getencprop (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,size_t) ; 
 size_t OF_getproplen (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_keymap(phandle_t node, const char *prop, pcell_t **keymap, size_t *len)
{

	if ((*len = OF_getproplen(node, prop)) <= 0) {
		return (ENXIO);
	}
	if ((*keymap = malloc(*len, M_DEVBUF, M_NOWAIT)) == NULL) {
		return (ENOMEM);
	}
	if (OF_getencprop(node, prop, *keymap, *len) != *len) {
		return (ENXIO);
	}
	return (0);
}