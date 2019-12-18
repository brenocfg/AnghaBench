#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t size; TYPE_5__* entries; } ;
struct TYPE_8__ {TYPE_5__* base; } ;
struct TYPE_9__ {TYPE_1__ name; } ;
struct TYPE_10__ {TYPE_5__* base; } ;
struct TYPE_12__ {int type; TYPE_4__ elements; TYPE_2__ data; TYPE_3__ suffix; } ;
typedef  TYPE_5__ h2o_logconf_t ;

/* Variables and functions */
#define  ELEMENT_TYPE_EXTENDED_VAR 131 
#define  ELEMENT_TYPE_IN_HEADER_STRING 130 
#define  ELEMENT_TYPE_OUT_HEADER_STRING 129 
#define  ELEMENT_TYPE_TIMESTAMP_STRFTIME 128 
 int /*<<< orphan*/  free (TYPE_5__*) ; 

void h2o_logconf_dispose(h2o_logconf_t *logconf)
{
    size_t i;

    for (i = 0; i != logconf->elements.size; ++i) {
        free(logconf->elements.entries[i].suffix.base);
        switch (logconf->elements.entries[i].type) {
        case ELEMENT_TYPE_EXTENDED_VAR:
        case ELEMENT_TYPE_IN_HEADER_STRING:
        case ELEMENT_TYPE_OUT_HEADER_STRING:
        case ELEMENT_TYPE_TIMESTAMP_STRFTIME:
            free(logconf->elements.entries[i].data.name.base);
            break;
        default:
            break;
        }
    }
    free(logconf->elements.entries);
    free(logconf);
}