#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rlayer; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 scalar_t__ RECORD_LAYER_processed_read_pending (int /*<<< orphan*/ *) ; 
 int RECORD_LAYER_read_pending (int /*<<< orphan*/ *) ; 

int SSL_has_pending(const SSL *s)
{
    /*
     * Similar to SSL_pending() but returns a 1 to indicate that we have
     * unprocessed data available or 0 otherwise (as opposed to the number of
     * bytes available). Unlike SSL_pending() this will take into account
     * read_ahead data. A 1 return simply indicates that we have unprocessed
     * data. That data may not result in any application data, or we may fail
     * to parse the records for some reason.
     */
    if (RECORD_LAYER_processed_read_pending(&s->rlayer))
        return 1;

    return RECORD_LAYER_read_pending(&s->rlayer);
}