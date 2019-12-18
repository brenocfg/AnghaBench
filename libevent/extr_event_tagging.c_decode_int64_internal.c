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
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_INT_INTERNAL (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct evbuffer*,int) ; 

__attribute__((used)) static int
decode_int64_internal(ev_uint64_t *pnumber, struct evbuffer *evbuf, int offset)
{
	ev_uint64_t number = 0;
	DECODE_INT_INTERNAL(number, 16, pnumber, evbuf, offset);
}