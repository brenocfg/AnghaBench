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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tuple_callbacks {int id; int (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tuple_callbacks*,void*) ;} ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CISTPL_GENERIC ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tuple_callbacks*,void*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tuple_callbacks*,void*) ; 

__attribute__((used)) static int
decode_tuple(device_t cbdev, device_t child, int tupleid, int len,
    uint8_t *tupledata, uint32_t start, uint32_t *off,
    struct tuple_callbacks *callbacks, void *argp)
{
	int i;
	for (i = 0; callbacks[i].id != CISTPL_GENERIC; i++) {
		if (tupleid == callbacks[i].id)
			return (callbacks[i].func(cbdev, child, tupleid, len,
			    tupledata, start, off, &callbacks[i], argp));
	}
	return (callbacks[i].func(cbdev, child, tupleid, len,
	    tupledata, start, off, NULL, argp));
}