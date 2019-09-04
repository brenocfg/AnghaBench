#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t size; int /*<<< orphan*/ * bytes; TYPE_1__* _prototype; } ;
typedef  TYPE_2__ h2o_buffer_t ;
struct TYPE_5__ {TYPE_2__ _initial_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer__do_free (TYPE_2__*) ; 

void h2o_buffer_consume(h2o_buffer_t **_inbuf, size_t delta)
{
    h2o_buffer_t *inbuf = *_inbuf;

    if (delta != 0) {
        assert(inbuf->bytes != NULL);
        if (inbuf->size == delta) {
            *_inbuf = &inbuf->_prototype->_initial_buf;
            h2o_buffer__do_free(inbuf);
        } else {
            inbuf->size -= delta;
            inbuf->bytes += delta;
        }
    }
}