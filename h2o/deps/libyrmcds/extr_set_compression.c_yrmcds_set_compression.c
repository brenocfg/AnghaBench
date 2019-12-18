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
typedef  int /*<<< orphan*/  yrmcds_error ;
struct TYPE_3__ {size_t compress_size; } ;
typedef  TYPE_1__ yrmcds ;

/* Variables and functions */
 int /*<<< orphan*/  YRMCDS_BAD_ARGUMENT ; 
 int /*<<< orphan*/  YRMCDS_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  YRMCDS_OK ; 

yrmcds_error yrmcds_set_compression(yrmcds* c, size_t threshold) {
#ifdef LIBYRMCDS_USE_LZ4
    if( c == NULL )
        return YRMCDS_BAD_ARGUMENT;
    c->compress_size = threshold;
    return YRMCDS_OK;
#else
    return YRMCDS_NOT_IMPLEMENTED;
#endif
}